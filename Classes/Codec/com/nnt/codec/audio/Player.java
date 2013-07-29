package com.nnt.codec.audio;

public class Player extends com.nnt.codec.Object {
	
		public native boolean load(PCMStream stream);
		public native boolean play(String file);
		
}
