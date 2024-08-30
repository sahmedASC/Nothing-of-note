package edu.uiuc.cs427app;

import android.os.AsyncTask;
import android.os.Bundle;
import android.widget.TextView;

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

public class DetailsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_details);

        // Retrieve username to display on banner
        FirebaseAuth mAuth = FirebaseAuth.getInstance(); // Get authentication instance where user is logged in
        FirebaseUser user = mAuth.getCurrentUser(); // Get the current user
        String username = "";
        // If there is an active user, we are getting their Display Name (username) to set the app title
        if (user != null) {
            username += user.getDisplayName();
        }

        // API key required for calls to OpenWeather API (1000 free calls per day)
        String openWeatherAPIKey = "3ec6a11ce2902de24b4e73daeb2c5e05";

        // Update the banner to contain username after Team 33
        setTitle(getString(R.string.app_name,username));

        // Initialize TextViews
        TextView welcomeTextView = findViewById(R.id.welcomeText);

        // Process the Intent payload that has opened this Activity and show the information accordingly
        String cityName = getIntent().getStringExtra("locationName").toString();
        String welcome = "Welcome to "+cityName;
        welcomeTextView.setText(welcome);

        // Generic description about the contents of the page

        // Get the weather information from a Service that connects to a weather server and show the results
        new FetchWeatherTask().execute(openWeatherAPIKey, cityName);

    } // End of onCreate method

    private class FetchWeatherTask extends AsyncTask<String, Void, String> {
        protected String doInBackground(String... params) {
            String apiKey = params[0]; // First argument is OpenWeather API key
            String location = params[1]; // Second argument is the location/city name
            // Put together the URL that we are making calls to
            String apiURL = "https://api.openweathermap.org/data/2.5/weather?q=" + location
                    + "&appid=" + apiKey;

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

                    // Get temperature (this is in Kelvin, to be converted to Celsius afterwards)
                    double temperatureKelvin = json.getJSONObject("main").getDouble("temp");
                    int temperatureCelsius = (int) Math.round(temperatureKelvin - 273.15);

                    // Get weather conditions
                    JSONArray weatherArray = json.getJSONArray("weather");
                    String weatherDescription = weatherArray.getJSONObject(0).getString("description");

                    // Get humidity
                    int humidity = json.getJSONObject("main").getInt("humidity");

                    // Get wind speed
                    double windSpeed = json.getJSONObject("wind").getInt("speed");

                    // Update the corresponding TextView with the weather details
                    TextView weatherInfoTextView = findViewById(R.id.cityInfo);

                    // Set string with results - to be formatted better
                    String weatherInfo = "Temperature: " + temperatureCelsius + "\u2103\n\nWeather: " + weatherDescription +
                            "\n\nHumidity: " + humidity + "%\n\nWind Speed: " + windSpeed + "m/s";
                    weatherInfoTextView.setText(weatherInfo); // Set the information within the text view

                } catch (JSONException e) {
                    e.printStackTrace();
                }
            } else {
                TextView weatherInfoTextView = findViewById(R.id.cityInfo);
                weatherInfoTextView.setText("Invalid Location");
            }
        }
    }

}

