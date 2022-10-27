package gg.altis.luajit;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

// Copyright (C) Max Goddard 2020

public class LuaJIT {
	public static final String IMPL_VERSION = "1.0.0";
	public static final String IMPL_AUTHOR = "Max Goddard";
	
	public static final String VERSION = "Lua 5.1";
	public static final String RELEASE = "Lua 5.1.4";
	public static final int VERSION_NUM = 501;
	public static final String COPYRIGHT = "Copyright (C) 1994-2008 Lua.org, PUC-Rio";
	public static final String AUTHORS = "R. Ierusalimschy, L. H. de Figueiredo & W. Celes";
	public static final String SIGNATURE = "\033Lua";
	public static final int MULTRET = -1;
	public static final int REGISTRYINDEX = -10000;
	public static final int ENVIRONINDEX = -10001;
	public static final int GLOBALSINDEX = -10002;
	public static final int OK = 0;
	public static final int YIELD = 1;
	public static final int ERRRUN = 2;
	public static final int ERRSYNTAX = 3;
	public static final int ERRMEM = 4;
	public static final int ERRERR = 5;
	public static final int TNONE = -1;
	public static final int TNIL = 0;
	public static final int TBOOLEAN = 1;
	public static final int TLIGHTUSERDATA = 2;
	public static final int TNUMBER = 3;
	public static final int TSTRING = 4;
	public static final int TTABLE = 5;
	public static final int TFUNCTION = 6;
	public static final int TUSERDATA = 7;
	public static final int TTHREAD = 8;
	public static final int MINSTACK = 20;
	
	static {
		String os = System.getProperty("os.name").toLowerCase();
		String arch = System.getProperty("os.arch");
		
		File library = null;
		
		try {
			library = File.createTempFile("ljjb_" + IMPL_VERSION + "_", ".dll");
			library.deleteOnExit();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		
		FileOutputStream fos = null;
		
		try {
			fos = new FileOutputStream(library);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		String path = null;

		if (os.contains("win")) {
			if (arch.contains("64")) {
				path = "nativelibs/ljjb_w_x64.dll";
			} else {
				path = "nativelibs/ljjb_w_x32.dll";
			}
		} else if (os.contains("nix") || os.contains("nux") || os.contains("aix")) {
			
		} else if (os.contains("mac")) {
			
		}
		
		InputStream is = LuaJIT.class.getResourceAsStream(path);
		try {
			byte[] buffer = new byte[is.available()];
			is.read(buffer);
			fos.write(buffer);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				is.close();
				fos.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		System.load(library.getAbsolutePath());
	}
	
	// Load specific standard library.
	native public static void loadLibrary(long stateHandle, String library);
	
	// Load minimal standard libraries.
	native public static void loadMinimalLibraries(long stateHandle);
	
	native public static void atpanic(long stateHandle, LuaBindable panicf);
	native public static void call(long stateHandle, int nargs, int nresults);
	native public static int checkstack(long stateHandle, int n);
	native public static void close(long stateHandle);
	native public static void concat(long stateHandle, int n);
	native public static void createtable(long stateHandle, int narr, int nrec);
	native public static int error(long stateHandle);
	native public static int gc(long stateHandle, int what, int data);
	native public static void getfield(long stateHandle, int index, String k);
	native public static void getglobal(long stateHandle, String name);
	native public static int getmetatable(long stateHandle, int objindex);
	native public static void gettable(long stateHandle, int index);
	native public static int gettop(long stateHandle);
	native public static void insert(long stateHandle, int index);
	native public static int isboolean(long stateHandle, int index);
	native public static int iscfunction(long stateHandle, int index);
	native public static int isfunction(long stateHandle, int index);
	native public static int islightuserdata(long stateHandle, int index);
	native public static int isnil(long stateHandle, int index);
	native public static int isnone(long stateHandle, int index);
	native public static int isnoneornil(long stateHandle, int index);
	native public static int isnumber(long stateHandle, int index);
	native public static int isstring(long stateHandle, int index);
	native public static int istable(long stateHandle, int index);
	native public static int isthread(long stateHandle, int index);
	native public static int isuserdata(long stateHandle, int index);
	native public static void lessthan(long stateHandle, int index1, int index2);
	native public static void newtable(long stateHandle);
	native public static long newthread(long stateHandle);
	native public static int next(long stateHandle, int index);
	native public static long objlen(long stateHandle, int index);
	native public static int pcall(long stateHandle, int nargs, int nresults, int msgh);
	native public static void pop(long stateHandle, int n);
	native public static void pushboolean(long stateHandle, int b);
	native public static void pushcclosure(long stateHandle, LuaBindable fn, int n);
	native public static void pushcfunction(long stateHandle, LuaBindable f);
	native public static void pushinteger(long stateHandle, long n);
	native public static void pushlightuserdata(long stateHandle, Object p);
	native public static void pushnil(long stateHandle);
	native public static void pushnumber(long stateHandle, double n);
	native public static void pushstring(long stateHandle, String s);
	native public static void pushvalue(long stateHandle, int index);
	native public static int rawequal(long stateHandle, int index1, int index2);
	native public static void rawget(long stateHandle, int index);
	native public static void rawgeti(long stateHandle, int index, long n);
	native public static void rawset(long stateHandle, int index);
	native public static void rawseti(long stateHandle, int index, long i);
	native public static void register(long stateHandle, String name, LuaBindable function);
	native public static void remove(long stateHandle, int index);
	native public static void replace(long stateHandle, int index);
	native public static int resume(long stateHandle, int nargs);
	native public static void setfield(long stateHandle, int index, String k);
	native public static void setglobal(long stateHandle, String name);
	native public static void setmetatable(long stateHandle, int index);
	native public static void settable(long stateHandle, int index);
	native public static void settop(long stateHandle, int index);
	native public static int status(long stateHandle);
	native public static int toboolean(long stateHandle, int index);
	native public static long tointeger(long stateHandle, int index);
	native public static String tostring(long stateHandle, int index);
	native public static double tonumber(long stateHandle, int index);
	native public static long tothread(long stateHandle, int index);
	native public static Object touserdata(long stateHandle, int index);
	native public static int type(long stateHandle, int index);
	native public static String typename(long stateHandle, int tp);
	native public static double version(long stateHandle);
	native public static void xmove(long fromStateHandle, long toStateHandle, int n);
	native public static int yield(long stateHandle, int nresults);
	native public static void argcheck(long stateHandle, int cond, int arg, String extramsg);
	native public static int argerror(long stateHandle, int arg, String extramsg);
	native public static int callmeta(long stateHandle, int obj, String e);
	native public static void checkany(long stateHandle, int arg);
	native public static long checkinteger(long stateHandle, int arg);
	native public static String checkstring(long stateHandle, int arg);
	native public static double checknumber(long stateHandle, int arg);
	native public static void checkstack(long stateHandle, int sz, String msg);
	native public static void checktype(long stateHandle, int arg, int t);
	native public static Object checkudata(long stateHandle, int arg, String tname);
	native public static int dofile(long stateHandle, String filename);
	native public static int dostring(long stateHandle, String str);
	native public static int error(long stateHandle, String fmt);
	native public static int getmetafield(long stateHandle, int obj, String e);
	native public static void getmetatable(long stateHandle, String fname);
	native public static String gsub(long stateHandle, String s, String p, String r);
	native public static int loadfile(long stateHandle, String filename);
	native public static int loadstring(long stateHandle, String s);
	native public static int newmetatable(long stateHandle, String tname);
	native public static long newstate();
	native public static void openlibs(long stateHandle);
	native public static long optinteger(long stateHandle, int arg, long d);
	native public static double optnumber(long stateHandle, int arg, double d);
	native public static String optstring(long stateHandle, int arg, String d);
	native public static int ref(long stateHandle, int t);
	native public static void unref(long stateHandle, int t, int ref);
	native public static void where(long stateHandle, int lvl);
	
	public static int upvalueindex(int i) {
		return GLOBALSINDEX - i;
	}
}
