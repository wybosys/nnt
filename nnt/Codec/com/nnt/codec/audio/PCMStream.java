package com.nnt.codec.audio;

public class PCMStream extends Stream {

	public native boolean load(String file);
	
	static {
		System.loadLibrary("NntCodec");
	}
	
}
