/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;


import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Toast;
import c.mpayments.android.BillingActivity;
import c.mpayments.android.PurchaseListener;
import c.mpayments.android.PurchaseManager;
import c.mpayments.android.PurchaseRequest;
import c.mpayments.android.PurchaseResponse;

public class AppActivity extends Cocos2dxActivity {
	
	public static Activity act;
	
	/** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
    	super.onCreate(savedInstanceState);
        System.out.println("Super init");
        act = this;
    }
	
	public static void centiliPayment(String apikey) {
		PurchaseRequest pr = new PurchaseRequest(apikey);
		pr.setLanguageCode("en");
		pr.setClientId("centili_android_dev_team_test");
		pr.setTestModeEnabled(true);// Test mode enabled
		PurchaseManager.startPurchase(pr, act);
		BillingActivity.mcc = "220";//Hardcoded for Serbia
		BillingActivity.mnc = "05";// Operator VIP
		
		PurchaseManager.attachPurchaseListener(new PurchaseListener() {
			@Override
			public void onPurchaseSuccess(PurchaseResponse paramPurchaseResponse) {
				Toast.makeText(act,"onPurchaseSuccess " + ", Item name: " + paramPurchaseResponse.getItemName() + ", Amount: " + paramPurchaseResponse.getItemAmount() + ", Price: "
								+ paramPurchaseResponse.getPrice() + paramPurchaseResponse.getCurrency() + ", ClientID: " + paramPurchaseResponse.getClientId(), Toast.LENGTH_LONG).show();
			}

			@Override
			public void onPurchasePending(PurchaseResponse paramPurchaseResponse) {
				Toast.makeText(act, "onPurchasePending", Toast.LENGTH_SHORT).show();
			}

			@Override
			public void onPurchaseFailed(PurchaseResponse paramPurchaseResponse) {
				Toast.makeText(act, "onPurchaseFailed", Toast.LENGTH_LONG).show();
			}

			@Override
			public void onPurchaseCanceled(PurchaseResponse paramPurchaseResponse) {
				Toast.makeText(act, "onPurchaseCanceled", Toast.LENGTH_LONG).show();
			}
		});
	}
	
}
