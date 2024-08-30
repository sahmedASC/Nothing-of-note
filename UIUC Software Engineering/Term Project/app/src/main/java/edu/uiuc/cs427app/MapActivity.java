package edu.uiuc.cs427app;

import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class MapActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_map);

        // Retrieve username to display on banner
        FirebaseAuth mAuth = FirebaseAuth.getInstance(); // Get authentication instance where user is logged in
        FirebaseUser user = mAuth.getCurrentUser(); // Get the current user
        String username = "";
        // If there is an active user, we are getting their Display Name (username) to set the app title
        if (user != null) {
            username += user.getDisplayName();
        }

        // Update the banner to contain username after Team 33
        setTitle(getString(R.string.app_name,username));

        TextView mapWelcome = findViewById(R.id.mapTitle);

        // API key required for calls to OpenWeather API (1000 free calls per day)
        String openWeatherAPIKey = "3ec6a11ce2902de24b4e73daeb2c5e05";

        // Process the Intent payload that has opened this Activity and show the information accordingly
        String cityName = getIntent().getStringExtra("locationName").toString();
        String cityWeatherInfo = "Map of "+cityName;

        mapWelcome.setText(cityWeatherInfo);

        // Get the weather information from a Service that connects to a weather server and show the results
        new FetchWeatherTask().execute(openWeatherAPIKey, cityName);

    }//End of Create Method

    private class FetchWeatherTask extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... params) {
            String apiKey = params[0]; // First argument is OpenWeather API key
            String location = params[1]; // Second argument is the location/city name
            // Put together the URL that we are making calls to
            String apiURL = "https://api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=" + apiKey;

            // Below block of code tries to makes a connection to the OpenWeather API
            try {
                URL url = new URL(apiURL); // Create URL object
                HttpURLConnection connection = (HttpURLConnection) url.openConnection(); // Make connection

                // Check for successful connection
                if(connection.getResponseCode() == 200) {
                    InputStream inputStream = connection.getInputStream(); // Initialize input stream
                    // Create buffered reader utilizing initialized input stream
                    BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
                    StringBuilder result = new StringBuilder(); // Initialize result

                    String line; // Initialize "line" to store details and add to "result"

                    // Add lines to "result" in a while loop
                    while ((line = reader.readLine()) != null) {
                        result.append(line); // Add each line (iterative method)
                    }
                    return result.toString(); // Make the result String type
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            return null;
        }

        @Override
        protected void onPostExecute(String result) {
            if (result != null) {
                try {
                    JSONObject json = new JSONObject(result); // Use result to make a JSON object

                    double longitude = json.getJSONObject("coord").getDouble("lon");
                    double latitude = json.getJSONObject("coord").getDouble("lat");

                    // Update the corresponding TextView with the weather details
                    TextView latlongInfoTextView = findViewById(R.id.latlong);
                    String latlongtext = "Lat: "+ latitude + " Lon: " + longitude;
                    latlongInfoTextView.setText(latlongtext);

                    // Generate the embedding URL
                    String mapEmbedUrl = "https://www.google.com/maps/@"+ latitude+","+longitude+",11z?entry=ttu";

                    // Initialize WebView
                    WebView webView = findViewById(R.id.mapWebView);
                    WebSettings webSettings = webView.getSettings();
                    webSettings.setJavaScriptEnabled(true); // Enable JavaScript if needed

                    // Set a WebViewClient to handle redirects and avoid opening the browser
                    webView.setWebViewClient(new WebViewClient());

                    // Load the map URL into the WebView
                    webView.loadUrl(mapEmbedUrl);

                } catch (JSONException e) {
                    e.printStackTrace();
                }
            } else {
                TextView latlongInfoTextView = findViewById(R.id.latlong);
                latlongInfoTextView.setText("Invalid Location");
            }
        }
    }

}