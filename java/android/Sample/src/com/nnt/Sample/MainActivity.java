package com.nnt.Sample;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);		
		
		com.nnt.codec.audio.Player ply = new com.nnt.codec.audio.Player();
		com.nnt.codec.audio.PCMStream stm = new com.nnt.codec.audio.PCMStream();
		if (stm.load("music.mp3"))
			ply.load(stm);		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
