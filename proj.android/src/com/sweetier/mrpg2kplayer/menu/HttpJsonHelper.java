package com.sweetier.mrpg2kplayer.menu;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Iterator;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSession;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import org.json.JSONObject;

import android.os.AsyncTask;

public class HttpJsonHelper extends AsyncTask<Object, Void, JSONObject>{
 
	//url		:	https://google.com:1234/dir/helloworld.jsp �� ���� ��������, ��Ʈ, ȣ��Ʈ, ���ϸ��� ���Ե� ��ü URL
	//isPost	:	true�� ���		request�� ���� Json������ POST�� ����
	//				false�� ���	request�� ���� �ּ��� �ڿ� �پ� GET���� ����
	//				(�� GET�� �̿��� ��� request �Ʒ����� String�� ���� �ؾ��ϸ�, JSONObject �Ǵ� JSONArray�� ����� ��� ������ �۵��� �� �� �ִ�.)
	//request	:	BSONObject ������ ��û��
	//timeout	:	����ð� ����(ms ����, �⺻�� 60��)
	//listener	:	BSON ������ ������� �Ľ��� �Ǿ� �� �ݹ鿡 BSONObject �������� ��ȯ

	private final static int DEFAULT_TIMEOUT = 60000;//60��
	
	public static void run(String url, boolean isPost, JSONObject request, OnHttpHelperListener listener){
		new HttpJsonHelper().execute(url, isPost, request, DEFAULT_TIMEOUT, listener);
	}
	
	public static void run(String url, boolean isPost, JSONObject request, int timeout, OnHttpHelperListener listener){
		new HttpJsonHelper().execute(url, isPost, request, timeout, listener);
	}
	
	OnHttpHelperListener mListener;
	int resultCode;
 
	@Override
	protected JSONObject doInBackground(Object... params) {
		try {
			//�� �ʱ�ȭ
			String sUrl = (String) params[0];
			boolean isPost = (Boolean) params[1];
			JSONObject sBody = (JSONObject) params[2];
			int timeout = (Integer) params[3];
			mListener = (OnHttpHelperListener) params[4];
			
			URL url = new URL(sUrl);
			boolean isSequre = "https".equals(url.getProtocol());
			resultCode = -1;
			
			//���ؼ� ����
			HttpURLConnection conn = (HttpURLConnection) url.openConnection();
			
			//���۹�� ���� �� GET�̶�� �Ķ���� �Է�
			if(isPost){
				conn.setRequestMethod("POST");
			}else{
				conn.setRequestMethod("GET");
				boolean isFirst = true;
				
				StringBuilder sb = new StringBuilder(sUrl);
				
				String key, val;
				Iterator<String> keys = sBody.keys();
				while(keys.hasNext()){
					key = keys.next();
					val = (String)sBody.get(key);
					
					if(val == null || val.isEmpty())
						continue;
					
					sb.append(isFirst?'?':'&');
					sb.append(key);
					sb.append('=');
					sb.append(sBody.get(key));
					
					isFirst = false;
				}
				
				url = new URL(sb.toString());
			}
			
			//��Ÿ ����
			conn.setConnectTimeout(timeout);
			conn.setAllowUserInteraction(true);
			conn.setUseCaches(false);
			conn.setDoInput(true);
 
			conn.setRequestProperty("Cache-Control", "no-cache");
			conn.setRequestProperty("Content-Type", "application/json");
			//conn.setRequestProperty("Accept", "application/json");
			conn.setRequestProperty("Accept", "*");
			
			//https ����̶�� ��� host�� ����ϰ�(�������� host������ �������ؼ�..) �⺻ ��� ��ȣȭ(TSL)�� �����Ѵ�
			if(isSequre){
				TrustManager[] trustAllCerts = new TrustManager[] { new X509TrustManager() {
					public java.security.cert.X509Certificate[] getAcceptedIssuers() {return null;}
					public void checkClientTrusted(java.security.cert.X509Certificate[] certs, String authType) {}
					public void checkServerTrusted(java.security.cert.X509Certificate[] certs, String authType) {}
				} };
				
				SSLContext sslContext = SSLContext.getInstance("SSL");
				sslContext.init(null, trustAllCerts, null);
				
				HttpsURLConnection connS = (HttpsURLConnection)conn;
				connS.setSSLSocketFactory(sslContext.getSocketFactory());
				connS.setHostnameVerifier(new HostnameVerifier() {
					public boolean verify(String hostname, SSLSession session) {return true;}
				});
			}
 
			//POST�� request���� JSON���� ��ȯ�Ͽ� ��ȯ�Ѵ�.
			if(isPost){
				conn.setDoOutput(true);
				OutputStreamWriter osw = new OutputStreamWriter(conn.getOutputStream());
				osw.write(sBody.toString());
				osw.flush();
				osw.close();
			}
 
			//�������� ����� �Ǿ��ٸ� BSON�� �Ľ��Ѵ�
			resultCode = conn.getResponseCode();
			if (resultCode == HttpURLConnection.HTTP_OK) {
				InputStream in = conn.getInputStream();
				JSONObject result = new JSONObject(getStringFromInputStream(in));

				return result;
			}
 
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
		return null;
	}
 
	@Override
	protected void onPostExecute(JSONObject result) {
		if (mListener != null){
			if (result != null) 
				mListener.onReceived(result);
			else 
				mListener.onError(resultCode);
		}
	}
	
	private static String getStringFromInputStream(InputStream is) {

		BufferedReader br = null;
		StringBuilder sb = new StringBuilder();

		String line;
		try {

			br = new BufferedReader(new InputStreamReader(is));
			while ((line = br.readLine()) != null) {
				sb.append(line);
			}

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (br != null) {
				try {
					br.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}

		return sb.toString();

	}
}
