package gg.altis.luajit;

// Copyright (C) Max Goddard 2020

public class Test {
	public static void main(String[] args) {
		long s = LuaJIT.newstate();
		LuaJIT.openlibs(s);
		
		LuaJIT.pushcfunction(s, (stateHandle) -> {
			System.out.println("Hello, world!");
			return 0;
		});
		LuaJIT.setglobal(s, "say_hello");
		
		LuaJIT.dostring(s, "say_hello()");
	}
}
