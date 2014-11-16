package com.sagapps.pebblepaniccomp;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.provider.ContactsContract.CommonDataKinds.Phone;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;


public class MainActivity extends Activity {
	
	public static final int CONTACT_PICKER_RESULT = 1001;

	private static final String DEBUG_TAG = null;
	
	private Button chooseContact;
	private Button addContact;
	private EditText contactName;
	private EditText contactPhoneNum;
	private ArrayAdapter<String> mAdapter;
	private List<String> contacts;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        chooseContact = (Button) findViewById(R.id.btnChooseContact);
        addContact = (Button) findViewById(R.id.btnAddContact);
        contactName = (EditText) findViewById(R.id.txtContactName);
        contactPhoneNum = (EditText) findViewById(R.id.txtPhoneNum);
        contacts = new ArrayList<String>();
        
        chooseContact.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				/*Intent intent = new Intent(Intent.ACTION_PICK, ContactsContract.Contacts.CONTENT_URI);
				startActivityForResult(intent, PICK_CONTACT);*/
				Intent i = new Intent(Intent.ACTION_PICK,
                        ContactsContract.CommonDataKinds.Phone.CONTENT_URI);
                startActivityForResult(i, CONTACT_PICKER_RESULT);
				
			}
		});
    }
    
   
    
    @Override
    protected void onActivityResult(int reqCode, int resultCode, Intent data) {
    	/*super.onActivityResult(reqCode, resultCode, data);
    	switch(reqCode){
    	case(PICK_CONTACT):
    		if(resultCode == Activity.RESULT_OK){
    			Uri contactData = data.getData();
    			Cursor c = managedQuery(contactData, null, null, null, null);
    			if(c.moveToFirst()){
    				String name = c.getString(c.getColumnIndexOrThrow(People.NAME));
    				int number =  c.getInt(c.getColumnIndexOrThrow(People.NUMBER));
    				contactName.setText(name);
    				contactPhoneNum.setText(number);
    			}
    		}
    	}*/
    	super.onActivityResult(reqCode, resultCode, data);
        if(resultCode == RESULT_OK) {
            switch (reqCode) {
            case CONTACT_PICKER_RESULT:
                Cursor cursor = null;
                String number = "";
                String name ="";
                try {

                    Uri result = data.getData();

                    //get the id from the uri
                    String id = result.getLastPathSegment();  

                    //query
                    cursor = getContentResolver().query(
                            ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
                            null,
                            ContactsContract.CommonDataKinds.Phone._ID + " = ? " , new String[] {id}, null);

                    //int numberIdx = cursor.getColumnIndex(Phone.DATA);  

                  //Get Name
                    cursor = getContentResolver().query(result, null, null, null, null);
                    if (cursor.moveToFirst()) {
                        name = cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME));
                        number = cursor.getString(cursor.getColumnIndex(ContactsContract.CommonDataKinds.Phone.NUMBER));
                    } 
                
          
             

                }catch(Exception e){
                	Log.d(""+e,"line 111");
                }
                contactPhoneNum.setText(number);
                contactName.setText(name);
            }
        }
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
