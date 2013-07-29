package com.nnt.codec;

public abstract class Object extends com.nnt.java.Object {

	static {
		System.loadLibrary("NntJava");
		System.loadLibrary("NntCodec");
	}
	
}
