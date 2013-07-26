package com.nnt;

public class Java {
	
	private native void Test();
	
	public static void Load() {
		Java obj = new Java();
		obj.Test();
	}
	
	static {
		System.loadLibrary("NntJava");
	}

}
