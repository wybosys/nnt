package com.nnt.codec.audio;

public class Player {
	
		public native boolean load(PCMStream stream);

		static {
			System.loadLibrary("NntCodec");
		}
		
}
