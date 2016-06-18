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

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class AppActivity extends Cocos2dxActivity 
{
    private static AppActivity instance;

    public static Handler handler;

   protected void onCreate(Bundle savedInstanceState)
   {
	   super.onCreate(savedInstanceState);
	   
	   instance = this;
	   
	   handler = new Handler()
	   {
		   @Override
           public void handleMessage(Message msg) 
		   {
               // TODO Auto-generated method stub
               //super.handleMessage(msg);
			   switch (msg.what) 
			   {
			   case 1:
				   
				  Log.i("TBU_DEBUG","handleMessage");
				  AlertDialog.Builder builder = new AlertDialog.Builder(instance);
				   builder.setTitle("确定退出游戏吗？")
				   .setPositiveButton("确定", new OnClickListener() 
				   {
					@Override
					public void onClick(DialogInterface dialog, int which) 
					{
						// TODO Auto-generated method stub
						 System.exit(0);
					}
				}).setNegativeButton("取消", null)
				.show();
				   
				   break;
	              default:
	               break;
			   }
		   }
	   };
	   
   }
   
   //被c++调用的方法，发送消息到Handler
   public static void exitGame()
   {
	   Log.i("TBU_DEBUG","exitGame...");
       Message msg = Message.obtain();
       msg.what = 1;
       handler.sendMessage(msg);
   }
}
   


