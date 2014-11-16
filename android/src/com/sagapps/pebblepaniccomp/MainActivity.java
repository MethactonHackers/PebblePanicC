package com.sagapps.pebblepaniccomp;

import java.util.ArrayList;
import java.util.UUID;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.telephony.SmsManager;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import com.getpebble.android.kit.PebbleKit;
import com.getpebble.android.kit.PebbleKit.PebbleDataReceiver;
import com.getpebble.android.kit.util.PebbleDictionary;

public class MainActivity extends Activity {

	public static final int CONTACT_PICKER_RESULT = 1001;
	private static final String DEBUG_TAG = null;
	private static final int BUTTON_UP = 1;
	private static final int BUTTON_SELECT = 2;
	private static final int BUTTON_DOWN = 3;
	private final static UUID PEBBLE_APP_UUID = UUID
			.fromString("044f1e24-f686-45f7-a22d-23116f8ae92c");
	private final static String APP_UUID = "044f1e24-f686-45f7-a22d-23116f8ae92c";
	private Button chooseContact;
	private Button addContact;
	private EditText contactName;
	private EditText contactPhoneNum;
	private int num;
	private ArrayAdapter<String> mAdapter;
	private ListView lv;
	private ArrayList<String> contacts;
	private ArrayList<String> contactNums;
	private Button send;
	private PebbleDataReceiver mReceiver;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		chooseContact = (Button) findViewById(R.id.btnChooseContact);
		addContact = (Button) findViewById(R.id.btnAddContact);
		addContact.setVisibility(View.INVISIBLE);
		contactName = (EditText) findViewById(R.id.txtContactName);
		contactPhoneNum = (EditText) findViewById(R.id.txtPhoneNum);
		lv = (ListView) findViewById(R.id.listView1);
		contacts = new ArrayList<String>();
		contactNums = new ArrayList<String>();
		send = (Button) findViewById(R.id.btnSend);
		send.setVisibility(View.GONE);

		chooseContact.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent i = new Intent(Intent.ACTION_PICK,
						ContactsContract.CommonDataKinds.Phone.CONTENT_URI);
				startActivityForResult(i, CONTACT_PICKER_RESULT);
			}
		});

		addContact.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				mAdapter = new ArrayAdapter<String>(MainActivity.this,
						android.R.layout.simple_list_item_1, contacts);
				lv.setAdapter(mAdapter);
			}
		});

		send.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				for (int c = 0; c < contactNums.size(); c++) {
					String phoneNo = contactNums.get(c);
					String sms = "testing pebble panic";

					try {
						SmsManager smsManager = SmsManager.getDefault();
						smsManager.sendTextMessage(phoneNo, null, sms, null,
								null);
						Toast.makeText(getApplicationContext(), "SMS Sent!",
								Toast.LENGTH_LONG).show();
					} catch (Exception e) {
						Toast.makeText(getApplicationContext(),
								"SMS faild, please try again later!",
								Toast.LENGTH_LONG).show();
						e.printStackTrace();
					}
				}

			}
		});

	}

	@Override
	protected void onActivityResult(int reqCode, int resultCode, Intent data) {
		super.onActivityResult(reqCode, resultCode, data);
		if (resultCode == RESULT_OK) {
			switch (reqCode) {
			case CONTACT_PICKER_RESULT:
				Cursor cursor = null;
				String number = "";
				String name = "";
				try {

					Uri result = data.getData();

					// get the id from the uri
					String id = result.getLastPathSegment();

					// query
					cursor = getContentResolver().query(
							ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
							null,
							ContactsContract.CommonDataKinds.Phone._ID
									+ " = ? ", new String[] { id }, null);

					// int numberIdx = cursor.getColumnIndex(Phone.DATA);

					// Get Name
					cursor = getContentResolver().query(result, null, null,
							null, null);
					if (cursor.moveToFirst()) {
						name = cursor
								.getString(cursor
										.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME));
						number = cursor
								.getString(cursor
										.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER));
					}

				} catch (Exception e) {
					Log.d("" + e, "line 111");
				}
				contactPhoneNum.setText(number);
				contactName.setText(name);
				contacts.add(name);
				contactNums.add(number);
				// Toast.makeText(getApplicationContext(), contactNums+"",
				// Toast.LENGTH_SHORT).show();
				// num = onlyDigits(contactPhoneNum.toString());
				// Toast.makeText(getApplicationContext(), "fone number"+num,
				// Toast.LENGTH_LONG).show();
				addContact.setVisibility(View.VISIBLE);

			}
		}
	}

	@Override
	public void onResume() {
		super.onResume();

		// Start the companion app on the watch
		// PebbleKit.startAppOnPebble(getApplicationContext(),
		// "044f1e24-f686-45f7-a22d-23116f8ae92c");

		mReceiver = new PebbleDataReceiver(UUID.fromString(APP_UUID)) {

			@Override
			public void receiveData(Context context, int transactionId,
					PebbleDictionary data) {
				// TODO Auto-generated method stub
				PebbleKit.sendAckToPebble(context, transactionId);

				System.out.print(transactionId);
				send.performClick();

			}
		};
		PebbleKit.registerReceivedDataHandler(this, mReceiver);
	}

	@Override
	public void onPause() {
		super.onPause();

		unregisterReceiver(mReceiver);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
