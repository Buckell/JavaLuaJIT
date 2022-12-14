/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class gg_altis_luajit_LuaJIT */

#ifndef _Included_gg_altis_luajit_LuaJIT
#define _Included_gg_altis_luajit_LuaJIT
#ifdef __cplusplus
extern "C" {
#endif
	
/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    loadLibrary
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_loadLibrary
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    loadMinimalLibraries
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_loadMinimalLibraries
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    atpanic
 * Signature: (JLgg/altis/luajit/LuaBindable;)Lgg/altis/luajit/LuaBindable;
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_atpanic
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    call
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_call
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkstack
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_checkstack__JI
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_close
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    concat
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_concat
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    createtable
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_createtable
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    error
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_error__J
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    gc
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_gc
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getfield
 * Signature: (JILjava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_getfield
  (JNIEnv *, jclass, jlong, jint, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getglobal
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_getglobal
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getmetatable
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_getmetatable__JI
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    gettable
 * Signature: (JI)I
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_gettable
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    gettop
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_gettop
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    insert
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_insert
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isboolean
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isboolean
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    iscfunction
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_iscfunction
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isfunction
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isfunction
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    islightuserdata
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_islightuserdata
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isnil
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isnil
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isnone
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isnone
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isnoneornil
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isnoneornil
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isnumber
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isnumber
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isstring
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isstring
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    istable
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_istable
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isthread
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isthread
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    isuserdata
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_isuserdata
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    lessthan
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_lessthan
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    newtable
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_newtable
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    newthread
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_newthread
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    next
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_next
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    objlen
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_objlen
(JNIEnv*, jclass, jlong, jint);


/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pcall
 * Signature: (JIII)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_pcall
  (JNIEnv *, jclass, jlong, jint, jint, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pop
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pop
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushboolean
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushboolean
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushcclosure
 * Signature: (JLgg/altis/luajit/LuaBindable;I)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushcclosure
  (JNIEnv *, jclass, jlong, jobject, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushcfunction
 * Signature: (JLgg/altis/luajit/LuaBindable;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushcfunction
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushinteger
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushinteger
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushlightuserdata
 * Signature: (JLjava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushlightuserdata
  (JNIEnv *, jclass, jlong, jobject);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushnil
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushnil
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushnumber
 * Signature: (JD)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushnumber
  (JNIEnv *, jclass, jlong, jdouble);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushstring
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushstring
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    pushvalue
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_pushvalue
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawequal
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_rawequal
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawget
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_rawget
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawgeti
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_rawgeti
  (JNIEnv *, jclass, jlong, jint, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawset
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_rawset
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    rawseti
 * Signature: (JIJ)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_rawseti
  (JNIEnv *, jclass, jlong, jint, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    register
 * Signature: (JLjava/lang/String;Lgg/altis/luajit/LuaBindable;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_register
  (JNIEnv *, jclass, jlong, jstring, jobject);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    remove
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_remove
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    replace
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_replace
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    resume
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_resume
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    setfield
 * Signature: (JILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_setfield
  (JNIEnv *, jclass, jlong, jint, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    setglobal
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_setglobal
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    setmetatable
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_setmetatable__JI
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    settable
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_settable
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    settop
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_settop
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    status
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_status
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    toboolean
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_toboolean
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    tointeger
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_tointeger
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    tostring
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_tostring
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    tonumber
 * Signature: (JI)D
 */
JNIEXPORT jdouble JNICALL Java_gg_altis_luajit_LuaJIT_tonumber
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    tothread
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_tothread
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    touserdata
 * Signature: (JI)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_gg_altis_luajit_LuaJIT_touserdata
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    type
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_type
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    typename
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_typename
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    upvalueindex
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_upvalueindex
  (JNIEnv *, jclass, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    version
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_gg_altis_luajit_LuaJIT_version
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    xmove
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_xmove
  (JNIEnv *, jclass, jlong, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    yield
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_yield
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    argcheck
 * Signature: (JIILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_argcheck
  (JNIEnv *, jclass, jlong, jint, jint, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    argerror
 * Signature: (JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_argerror
  (JNIEnv *, jclass, jlong, jint, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    callmeta
 * Signature: (JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_callmeta
  (JNIEnv *, jclass, jlong, jint, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkany
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_checkany
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkinteger
 * Signature: (JI)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_checkinteger
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkstring
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_checkstring
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checknumber
 * Signature: (JI)D
 */
JNIEXPORT jdouble JNICALL Java_gg_altis_luajit_LuaJIT_checknumber
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkstack
 * Signature: (JILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_checkstack__JILjava_lang_String_2
  (JNIEnv *, jclass, jlong, jint, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checktype
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_checktype
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    checkudata
 * Signature: (JILjava/lang/String;)Ljava/lang/Object;
 */
JNIEXPORT jobject JNICALL Java_gg_altis_luajit_LuaJIT_checkudata
  (JNIEnv *, jclass, jlong, jint, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    dofile
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_dofile
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    dostring
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_dostring
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    error
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_error__JLjava_lang_String_2
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getmetafield
 * Signature: (JILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_getmetafield
  (JNIEnv *, jclass, jlong, jint, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    getmetatable
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_getmetatable__JLjava_lang_String_2
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    gsub
 * Signature: (JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_gsub
  (JNIEnv *, jclass, jlong, jstring, jstring, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    loadfile
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_loadfile
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    loadstring
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_loadstring
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    newmetatable
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_newmetatable
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    newstate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_newstate
  (JNIEnv *, jclass);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    openlibs
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_openlibs
  (JNIEnv *, jclass, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    optinteger
 * Signature: (JIJ)J
 */
JNIEXPORT jlong JNICALL Java_gg_altis_luajit_LuaJIT_optinteger
  (JNIEnv *, jclass, jlong, jint, jlong);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    optnumber
 * Signature: (JID)D
 */
JNIEXPORT jdouble JNICALL Java_gg_altis_luajit_LuaJIT_optnumber
  (JNIEnv *, jclass, jlong, jint, jdouble);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    optstring
 * Signature: (JILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_gg_altis_luajit_LuaJIT_optstring
  (JNIEnv *, jclass, jlong, jint, jstring);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    ref
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_gg_altis_luajit_LuaJIT_ref
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    unref
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_unref
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     gg_altis_luajit_LuaJIT
 * Method:    where
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_gg_altis_luajit_LuaJIT_where
  (JNIEnv *, jclass, jlong, jint);

#ifdef __cplusplus
}
#endif
#endif
