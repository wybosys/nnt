package com.nnt.core;

public class Nnt {

	public static native String VersionStr();
	
	static {
		System.loadLibrary("NntCore");
	}
	
}
