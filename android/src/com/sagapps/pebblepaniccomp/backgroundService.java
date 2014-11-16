/*package com.sagapps.pebblepaniccomp;

import android.app.IntentService;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

public class backgroundService extends IntentService {
	   public backgroundService(String name) {
		super(name);
		// TODO Auto-generated constructor stub
	}

	@Override
	   public IBinder onBind(Intent arg0) {
	      return null;
	   }

	   @Override
	   public int onStartCommand(Intent intent, int flags, int startId) {
	      // Let it continue running until it is stopped.
	      Toast.makeText(this, "Service Started", Toast.LENGTH_LONG).show();
	     Log.d("Service Started","Service Started");
	      return START_STICKY;
	   }
	   @Override
	   public void onDestroy() {
	      super.onDestroy();
	      Toast.makeText(this, "Service Destroyed", Toast.LENGTH_LONG).show();
	      Log.d("Service Destroyed","Service Destroyed");
		     
	   }

	@Override
	protected void onHandleIntent(Intent intent) {
		// TODO Auto-generated method stub
		Toast.makeText(this, "Service Started", Toast.LENGTH_LONG).show();
	}
	}
*/