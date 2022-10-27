// Copyright (C) Max Goddard 2020

#include <string_view>
#include <set>
#include <iostream>
#include <thread>

#include <lua.hpp>

#include "gg_altis_luajit_LuaJIT.h"

static std::set<jobject> to_collect;

union state_conversion {
	jlong handle;
	lua_State* L;
};

static void load_standard_library(lua_State* L, const std::string_view library_name) {
	if (library_name == "base") {
		lua_pushcfunction(L, luaopen_base);
		lua_pushstring(L, "");
		lua_call(L, 1, 0);
	} else if (library_name == "table") {
		lua_pushcfunction(L, luaopen_table);
		lua_pushstring(L, LUA_TABLIBNAME);
		lua_call(L, 1, 0);
	} else if (library_name == "string") {
		lua_pushcfunction(L, luaopen_string);
		lua_pushstring(L, LUA_STRLIBNAME);
		lua_call(L, 1, 0);
	} else if (library_name == "math") {
		lua_pushcfunction(L, luaopen_math);
		lua_pushstring(L, LUA_MATHLIBNAME);
		lua_call(L, 1, 0);
	} else if (library_name == "debug") {
		lua_pushcfunction(L, luaopen_debug);
		lua_pushstring(L, LUA_DBLIBNAME);
		lua_call(L, 1, 0);
	} else if (library_name == "io") {
		lua_pushcfunction(L, luaopen_io);
		lua_pushstring(L, LUA_IOLIBNAME);
		lua_call(L, 1, 0);
	} else if (library_name == "os") {
		lua_pushcfunction(L, luaopen_os);
		lua_pushstring(L, LUA_OSLIBNAME);
		lua_call(L, 1, 0);
	} else if (library_name == "package") {
		lua_pushcfunction(L, luaopen_package);
		lua_pushstring(L, LUA_LOADLIBNAME);
		lua_call(L, 1, 0);
	}
}

int java_function_bind(lua_State* L) {
	lua_getglobal(L, "_JENV");
	JNIEnv* env = (JNIEnv*)lua_touserdata(L, -1);
	lua_pop(L, 1);

	jobject bindable = (jobject)lua_touserdata(L, lua_upvalueindex(1));

	jmethodID mid = (jmethodID)lua_touserdata(L, lua_upvalueindex(2));

	state_conversion conv;
	conv.L = L;

	return env->CallIntMethod(bindable, mid, conv.handle);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    loadLibrary
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_loadLibrary
(JNIEnv* env, jclass, jlong state_handle, jstring library_name) {
	const char* c_library_name = env->GetStringUTFChars(library_name, nullptr);
	load_standard_library(state_conversion{ state_handle }.L, c_library_name);
	env->ReleaseStringUTFChars(library_name, c_library_name);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    loadMinimalLibraries
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_loadMinimalLibraries
(JNIEnv* env, jclass, jlong state_handle) {
	state_conversion conv{ state_handle };
	load_standard_library(conv.L, "base");
	load_standard_library(conv.L, LUA_TABLIBNAME);
	load_standard_library(conv.L, LUA_STRLIBNAME);
	load_standard_library(conv.L, LUA_MATHLIBNAME);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    atpanic
 * Signature: (JLgg/altis/luajit/LuaBindable;)Lgg/altis/luajit/LuaBindable;
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_atpanic
(JNIEnv* env, jclass, jlong state_handle, jobject panicf) {
	state_conversion conv{ state_handle };
		
	lua_getglobal(conv.L, "_JREG");
	lua_pushlightuserdata(conv.L, env->NewGlobalRef(panicf));
	lua_setfield(conv.L, -2, "atpanic");

	lua_atpanic(conv.L, [](lua_State* L) -> int {
		lua_getglobal(L, "_JENV");
		JNIEnv* env = (JNIEnv*)lua_touserdata(L, -1);
		lua_pop(L, 1);

		lua_getglobal(L, "_JREG");
		lua_getfield(L, lua_gettop(L), "atpanic");
		jobject panicf = (jobject)lua_touserdata(L, -1);
		lua_pop(L, 2);

		state_conversion conv;
		conv.L = L;

		return env->CallIntMethod(panicf, env->GetMethodID(env->GetObjectClass(panicf), "run", "(J)I"), conv.handle);
	});
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    call
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_call
(JNIEnv*, jclass, jlong state_handle, jint nargs, jint nresults) {
	lua_call(state_conversion{ state_handle }.L, nargs, nresults);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkstack
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_checkstack__JI
(JNIEnv*, jclass, jlong state_handle, jint sz) {
	return lua_checkstack(state_conversion{ state_handle }.L, sz);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_close
(JNIEnv* env, jclass, jlong state_handle) {
	state_conversion conv{ state_handle };

	lua_settop(conv.L, 0);

	lua_getglobal(conv.L, "_JREG");
	lua_pushnil(conv.L);
	while (lua_next(conv.L, 1)) {
		env->DeleteGlobalRef((jobject)lua_touserdata(conv.L, -1));
		lua_pop(conv.L, 1);
	}

	for (jobject obj : to_collect) {
		env->DeleteGlobalRef(obj);
	}
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    concat
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_concat
(JNIEnv*, jclass, jlong state_handle, jint n) {
	lua_concat(state_conversion{ state_handle }.L, n);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    createtable
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_createtable
(JNIEnv*, jclass, jlong state_handle, jint narr, jint nrec) {
	lua_createtable(state_conversion{ state_handle }.L, narr, nrec);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    error
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_error__J
(JNIEnv*, jclass, jlong state_handle) {
	return lua_error(state_conversion{ state_handle }.L);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    gc
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_gc
(JNIEnv*, jclass, jlong state_handle, jint what, jint data) {
	return lua_gc(state_conversion{ state_handle }.L, what, data);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getfield
 * Signature: (JILjava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_getfield
(JNIEnv* env, jclass, jlong state_handle, jint index, jstring k) {
	const char* c_k = env->GetStringUTFChars(k, nullptr);
	lua_getfield(state_conversion{ state_handle }.L, index, c_k);
	env->ReleaseStringUTFChars(k, c_k);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getglobal
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_getglobal
(JNIEnv* env, jclass, jlong state_handle, jstring name) {
	const char* c_name = env->GetStringUTFChars(name, nullptr);
	lua_getglobal(state_conversion{ state_handle }.L, c_name);
	env->ReleaseStringUTFChars(name, c_name);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getmetatable
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_getmetatable__JI
(JNIEnv*, jclass, jlong state_handle, jint objindex) {
	return lua_getmetatable(state_conversion{ state_handle }.L, objindex);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    gettable
 * Signature: (JI)I
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_gettable
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_gettable(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    gettop
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_gettop
(JNIEnv*, jclass, jlong state_handle) {
	return lua_gettop(state_conversion{ state_handle }.L);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    insert
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_insert
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_insert(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isboolean
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isboolean
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_isboolean(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    iscfunction
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_iscfunction
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_iscfunction(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isfunction
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isfunction
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_isfunction(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    islightuserdata
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_islightuserdata
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_islightuserdata(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isnil
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isnil
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_isnil(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isnone
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isnone
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_isnone(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isnoneornil
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isnoneornil
(JNIEnv*, jclass, jlong state_handle , jint index) {
	return lua_isnoneornil(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isnumber
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isnumber
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_isnumber(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isstring
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isstring
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_isstring(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    istable
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_istable
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_istable(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isthread
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isthread
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_isthread(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isuserdata
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isuserdata
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_isuserdata(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    lessthan
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_lessthan
(JNIEnv*, jclass, jlong state_handle, jint index1, jint index2) {
	return lua_lessthan(state_conversion{ state_handle }.L, index1, index2);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    newtable
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_newtable
(JNIEnv*, jclass, jlong state_handle) {
	lua_newtable(state_conversion{ state_handle }.L);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    newthread
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_newthread
(JNIEnv*, jclass, jlong state_handle) {
	state_conversion conv;
	conv.L = lua_newthread(state_conversion{ state_handle }.L);
	return conv.handle;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    next
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_next
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_next(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    objlen
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_objlen
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_objlen(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pcall
 * Signature: (JIII)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_pcall
(JNIEnv*, jclass, jlong state_handle, jint nargs, jint nresults, jint errfunc) {
	return lua_pcall(state_conversion{ state_handle }.L, nargs, nresults, errfunc);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pop
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pop
(JNIEnv*, jclass, jlong state_handle, jint n) {
	lua_pop(state_conversion{ state_handle }.L, n);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushboolean
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushboolean
(JNIEnv*, jclass, jlong state_handle, jint b) {
	lua_pushboolean(state_conversion{ state_handle }.L, b);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushcclosure
 * Signature: (JLgg/altis/luajit/LuaBindable;I)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushcclosure
(JNIEnv* env, jclass, jlong state_handle, jobject fn, jint n) {
	state_conversion conv{ state_handle };

	jobject global_ref = env->NewGlobalRef(fn);
	to_collect.insert(global_ref);

	lua_pushlightuserdata(conv.L, global_ref);
	lua_insert(conv.L, -1-n);
	lua_pushlightuserdata(conv.L, env->GetMethodID(env->GetObjectClass(fn), "run", "(J)I"));
	lua_insert(conv.L, -2-n);

	lua_pushcclosure(conv.L, java_function_bind, n + 2);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushcfunction
 * Signature: (JLgg/altis/luajit/LuaBindable;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushcfunction
(JNIEnv* env, jclass, jlong state_handle, jobject f) {
	state_conversion conv{ state_handle };

	jobject global_ref = env->NewGlobalRef(f);
	to_collect.insert(global_ref);

	lua_pushlightuserdata(conv.L, global_ref);
	lua_pushlightuserdata(conv.L, env->GetMethodID(env->GetObjectClass(f), "run", "(J)I"));

	lua_pushcclosure(conv.L, java_function_bind, 2);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushinteger
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushinteger
(JNIEnv*, jclass, jlong state_handle, jlong n) {
	lua_pushinteger(state_conversion{ state_handle }.L, n);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushlightuserdata
 * Signature: (JLjava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushlightuserdata
(JNIEnv* env, jclass, jlong state_handle, jobject p) {
	jobject global_ref = env->NewGlobalRef(p);
	to_collect.insert(global_ref);

	lua_pushlightuserdata(state_conversion{ state_handle }.L, global_ref);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushnil
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushnil
(JNIEnv*, jclass, jlong state_handle) {
	lua_pushnil(state_conversion{ state_handle }.L);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushnumber
 * Signature: (JD)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushnumber
(JNIEnv*, jclass, jlong state_handle, jdouble n) {
	lua_pushnumber(state_conversion{ state_handle }.L, n);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushstring
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushstring
(JNIEnv* env, jclass, jlong state_handle, jstring s) {
	const char* c_s = env->GetStringUTFChars(s, nullptr);
	lua_pushstring(state_conversion{ state_handle }.L, c_s);
	env->ReleaseStringUTFChars(s, c_s);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushvalue
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushvalue
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_pushvalue(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawequal
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_rawequal
(JNIEnv*, jclass, jlong state_handle, jint index1, jint index2) {
	return lua_rawequal(state_conversion{ state_handle }.L, index1, index2);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawget
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_rawget
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_rawget(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawgeti
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_rawgeti
(JNIEnv*, jclass, jlong state_handle, jint index, jlong n) {
	lua_rawgeti(state_conversion{ state_handle }.L, index, n);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawset
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_rawset
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_rawset(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawseti
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_rawseti
(JNIEnv*, jclass, jlong state_handle, jint index, jlong n) {
	lua_rawseti(state_conversion{ state_handle }.L, index, n);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    register
 * Signature: (JLjava/lang/String;Lgg/altis/luajit/LuaBindable;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_register
(JNIEnv* env, jclass, jlong state_handle, jstring name, jobject f) {
	state_conversion conv{ state_handle };
	const char* c_name = env->GetStringUTFChars(name, nullptr);
	jobject global_ref = env->NewGlobalRef(f);
	to_collect.insert(global_ref);

	lua_pushlightuserdata(conv.L, global_ref);
	lua_pushlightuserdata(conv.L, env->GetMethodID(env->GetObjectClass(f), "run", "(J)I"));
	lua_pushcclosure(conv.L, java_function_bind, 2);
	lua_setglobal(conv.L, c_name);

	env->ReleaseStringUTFChars(name, c_name);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    remove
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_remove
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_remove(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    replace
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_replace
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_replace(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    resume
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_resume
(JNIEnv*, jclass, jlong state_handle, jint narg) {
	return lua_resume(state_conversion{ state_handle }.L, narg);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    setfield
 * Signature: (JILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_setfield
(JNIEnv* env, jclass, jlong state_handle , jint index, jstring k) {
	const char* c_k = env->GetStringUTFChars(k, nullptr);
	lua_setfield(state_conversion{ state_handle }.L, index, c_k);
	env->ReleaseStringUTFChars(k, c_k);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    setglobal
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_setglobal
(JNIEnv* env, jclass, jlong state_handle, jstring name) {
	const char* c_name = env->GetStringUTFChars(name, nullptr);
	lua_setglobal(state_conversion{ state_handle }.L, c_name);
	env->ReleaseStringUTFChars(name, c_name);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    setmetatable
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_setmetatable__JI
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_setmetatable(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    settable
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_settable
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_settable(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    settop
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_settop
(JNIEnv*, jclass, jlong state_handle, jint index) {
	lua_settop(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    status
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_status
(JNIEnv*, jclass, jlong state_handle) {
	return lua_status(state_conversion{ state_handle }.L);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    toboolean
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_toboolean
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_toboolean(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    tointeger
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_tointeger
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_tointeger(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    tostring
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_tostring
(JNIEnv* env, jclass, jlong state_handle, jint index) {
	return env->NewStringUTF(lua_tostring(state_conversion{ state_handle }.L, index));
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    tonumber
 * Signature: (JI)D
 */
JNIEXPORT jdouble JNICALL Java_gg_altis_luajit_LuaJIT_tonumber
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_tonumber(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    tothread
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_tothread
(JNIEnv*, jclass, jlong state_handle, jint index) {
	state_conversion conv;
	conv.L = lua_tothread(state_conversion{ state_handle }.L, index);
	return conv.handle;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    touserdata
 * Signature: (JI)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_gg_altis_luajit_LuaJIT_touserdata
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return (jobject)lua_touserdata(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    type
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_type
(JNIEnv*, jclass, jlong state_handle, jint index) {
	return lua_type(state_conversion{ state_handle }.L, index);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    typename
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_typename
(JNIEnv* env, jclass, jlong state_handle, jint index) {
	return env->NewStringUTF(lua_typename(state_conversion{ state_handle }.L, index));
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    upvalueindex
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_upvalueindex
(JNIEnv*, jclass, jint i) {
	return lua_upvalueindex(i);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    version
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_gg_altis_luajit_LuaJIT_version
(JNIEnv*, jclass, jlong state_handle) {
	return 5.1;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    xmove
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_xmove
(JNIEnv*, jclass, jlong from_state_handle, jlong to_state_handle, jint n) {
	lua_xmove(state_conversion{ from_state_handle }.L, state_conversion{ to_state_handle }.L, n);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    yield
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_yield
(JNIEnv*, jclass, jlong state_handle, jint nresults) {
	return lua_yield(state_conversion{ state_handle }.L, nresults);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    argcheck
 * Signature: (JIILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_argcheck
(JNIEnv* env, jclass, jlong state_handle, jint cond, jint narg, jstring extramsg) {
	const char* c_extramsg = env->GetStringUTFChars(extramsg, nullptr);
	luaL_argcheck(state_conversion{ state_handle }.L, cond, narg, c_extramsg);
	env->ReleaseStringUTFChars(extramsg, c_extramsg);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    argerror
 * Signature: (JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_argerror
(JNIEnv* env, jclass, jlong state_handle, jint narg, jstring extramsg) {
	const char* c_extramsg = env->GetStringUTFChars(extramsg, nullptr);
	int ret = luaL_argerror(state_conversion{ state_handle }.L, narg, c_extramsg);
	env->ReleaseStringUTFChars(extramsg, c_extramsg);
	return ret;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    callmeta
 * Signature: (JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_callmeta
(JNIEnv* env, jclass, jlong state_handle, jint obj, jstring e) {
	const char* c_e = env->GetStringUTFChars(e, nullptr);
	int ret = luaL_callmeta(state_conversion{ state_handle }.L, obj, c_e);
	env->ReleaseStringUTFChars(e, c_e);
	return ret;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkany
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_checkany
(JNIEnv*, jclass, jlong state_handle, jint narg) {
	luaL_checkany(state_conversion{ state_handle }.L, narg);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkinteger
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_checkinteger
(JNIEnv*, jclass, jlong state_handle, jint narg) {
	return luaL_checkinteger(state_conversion{ state_handle }.L, narg);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkstring
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_checkstring
(JNIEnv* env, jclass, jlong state_handle, jint narg) {
	return env->NewStringUTF(luaL_checkstring(state_conversion{ state_handle }.L, narg));
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checknumber
 * Signature: (JI)D
 */
JNIEXPORT jdouble JNICALL Java_gg_altis_luajit_LuaJIT_checknumber
(JNIEnv*, jclass, jlong state_handle, jint narg) {
	return luaL_checknumber(state_conversion{ state_handle }.L, narg);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkstack
 * Signature: (JILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_checkstack__JILjava_lang_String_2
(JNIEnv* env, jclass, jlong state_handle, jint sz, jstring msg) {
	const char* c_msg = env->GetStringUTFChars(msg, nullptr);
	luaL_checkstack(state_conversion{ state_handle }.L, sz, c_msg);
	env->ReleaseStringUTFChars(msg, c_msg);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checktype
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_checktype
(JNIEnv*, jclass, jlong state_handle, jint arg, jint t) {
	luaL_checktype(state_conversion{ state_handle }.L, arg, t);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkudata
 * Signature: (JILjava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_gg_altis_luajit_LuaJIT_checkudata
(JNIEnv* env, jclass, jlong state_handle, jint arg, jstring tname) {
	const char* c_tname = env->GetStringUTFChars(tname, nullptr);
	void* udata = luaL_checkudata(state_conversion{ state_handle }.L, arg, c_tname);
	env->ReleaseStringUTFChars(tname, c_tname);
	return (jobject)udata;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    dofile
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_dofile
(JNIEnv* env, jclass, jlong state_handle, jstring filename) {
	const char* c_filename = env->GetStringUTFChars(filename, nullptr);
	int ret = luaL_dofile(state_conversion{ state_handle }.L, c_filename);
	env->ReleaseStringUTFChars(filename, c_filename);
	return ret;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    dostring
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_dostring
(JNIEnv* env, jclass, jlong state_handle, jstring str) {
	const char* c_str = env->GetStringUTFChars(str, nullptr);
	int ret = luaL_dostring(state_conversion{ state_handle }.L, c_str);
	env->ReleaseStringUTFChars(str, c_str);
	return ret;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    error
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_error__JLjava_lang_String_2
(JNIEnv* env, jclass, jlong state_handle, jstring fmt) {
	const char* c_fmt = env->GetStringUTFChars(fmt, nullptr);
	int ret = luaL_error(state_conversion{ state_handle }.L, c_fmt);
	env->ReleaseStringUTFChars(fmt, c_fmt);
	return ret;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getmetafield
 * Signature: (JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_getmetafield
(JNIEnv* env, jclass, jlong state_handle, jint obj, jstring e) {
	const char* c_e = env->GetStringUTFChars(e, nullptr);
	int ret = luaL_getmetafield(state_conversion{ state_handle }.L, obj, c_e);
	env->ReleaseStringUTFChars(e, c_e);
	return ret;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getmetatable
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_getmetatable__JLjava_lang_String_2
(JNIEnv* env, jclass, jlong state_handle, jstring fname) {
	const char* c_fname = env->GetStringUTFChars(fname, nullptr);
	luaL_getmetatable(state_conversion{ state_handle }.L, c_fname);
	env->ReleaseStringUTFChars(fname, c_fname);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    gsub
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_gsub
(JNIEnv* env, jclass, jlong state_handle, jstring s, jstring p, jstring r) {
	const char* c_s = env->GetStringUTFChars(s, nullptr);
	const char* c_p = env->GetStringUTFChars(p, nullptr);
	const char* c_r = env->GetStringUTFChars(r, nullptr);

	const char* ret = luaL_gsub(state_conversion{ state_handle }.L, c_s, c_s, c_r);

	env->ReleaseStringUTFChars(s, c_s);
	env->ReleaseStringUTFChars(p, c_p);
	env->ReleaseStringUTFChars(r, c_r);
	
	return env->NewStringUTF(ret);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    loadfile
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_loadfile
(JNIEnv* env, jclass, jlong state_handle, jstring filename) {
	const char* c_filename = env->GetStringUTFChars(filename, nullptr);
	int ret = luaL_loadfile(state_conversion{ state_handle }.L, c_filename);
	env->ReleaseStringUTFChars(filename, c_filename);
	return ret;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    loadstring
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_loadstring
(JNIEnv* env, jclass, jlong state_handle, jstring str) {
	const char* c_str = env->GetStringUTFChars(str, nullptr);
	int ret = luaL_loadfile(state_conversion{ state_handle }.L, c_str);
	env->ReleaseStringUTFChars(str, c_str);
	return ret;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    newmetatable
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_newmetatable
(JNIEnv* env, jclass, jlong state_handle, jstring tname) {
	const char* c_tname = env->GetStringUTFChars(tname, nullptr);
	int ret = luaL_newmetatable(state_conversion{ state_handle }.L, c_tname);
	env->ReleaseStringUTFChars(tname, c_tname);
	return ret;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    newstate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_newstate(JNIEnv* env, jclass) {
	lua_State* L = luaL_newstate();

	lua_pushlightuserdata(L, env);
	lua_setglobal(L, "_JENV");

	lua_newtable(L);
	lua_setglobal(L, "_JREG");

	state_conversion conv;
	conv.L = L;
	return conv.handle;
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    openlibs
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_openlibs
(JNIEnv*, jclass, jlong state_handle) {
	luaL_openlibs(state_conversion{ state_handle }.L);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    optinteger
 * Signature: (JIJ)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_optinteger
(JNIEnv*, jclass, jlong state_handle, jint narg, jlong d) {
	return luaL_optinteger(state_conversion{ state_handle }.L, narg, d);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    optnumber
 * Signature: (JID)D
 */
JNIEXPORT jdouble JNICALL Java_gg_altis_luajit_LuaJIT_optnumber
(JNIEnv*, jclass, jlong state_handle, jint narg, jdouble d) {
	return luaL_optnumber(state_conversion{ state_handle }.L, narg, d);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    optstring
 * Signature: (JILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_optstring
(JNIEnv* env, jclass, jlong state_handle, jint narg, jstring d) {
	const char* c_d = env->GetStringUTFChars(d, nullptr);
	const char* ret = luaL_optstring(state_conversion{ state_handle }.L, narg, c_d);
	env->ReleaseStringUTFChars(d, c_d);
	return env->NewStringUTF(ret);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    ref
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_ref
(JNIEnv*, jclass, jlong state_handle, jint t) {
	return luaL_ref(state_conversion{ state_handle }.L, t);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    unref
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_unref
(JNIEnv* env, jclass, jlong state_handle, jint t, jint ref) {
	return luaL_unref(state_conversion{ state_handle }.L, t, ref);
}

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    where
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_where
(JNIEnv*, jclass, jlong state_handle, jint lvl) {
	luaL_where(state_conversion{ state_handle }.L, lvl);
}