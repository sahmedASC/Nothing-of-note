package edu.uiuc.cs427app;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;
import androidx.navigation.ui.AppBarConfiguration;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.firestore.DocumentReference;
import com.google.firebase.firestore.FirebaseFirestore;
import com.google.firebase.firestore.QueryDocumentSnapshot;

import org.checkerframework.checker.nullness.qual.NonNull;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import edu.uiuc.cs427app.databinding.ActivityMainBinding;


public class MainActivity extends AppCompatActivity {

    private AppBarConfiguration appBarConfiguration;
    private ActivityMainBinding binding;

    private FirebaseFirestore firestore = FirebaseFirestore.getInstance(); // Initialize Firestore
    private Button addLocationButton;
    private ListView locationListView;
    private ArrayAdapter<String> locationAdapter;
    private List<String> locations;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

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

        // Set light/dark mode based on preference in Firestore
        retrieveAndSetVisualPreference();

        // Initializing button to add and remove locations from list of locations
        addLocationButton = findViewById(R.id.addLocationButton);
        locationListView = findViewById(R.id.locationListView); // View for the list of locations

        locations = new ArrayList<>(); // Where we will locally keep the list of locations after retrieval from Firestore
        // Creating locationAdapter - set location and button for each location saved for the user
        locationAdapter = new ArrayAdapter<String>(this, R.layout.list_item_locations, R.id.locationNameTextView, locations) {
            @NonNull
            @Override
            public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
                View view = super.getView(position, convertView, parent);

                // Get location name and "Show Details" button
                TextView locationNameTextview = view.findViewById(R.id.locationNameTextView);
                Button showDetailsButton = view.findViewById(R.id.showDetailsButton);
                Button showMapButton = view.findViewById(R.id.showMapButton);

                // Retrieve location name
                String locationName = getItem(position);

                // Set location name
                locationNameTextview.setText(locationName);

                // Handle "Show Weather" button click --> Details Activity
                showDetailsButton.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Intent detailsIntent = new Intent(MainActivity.this, DetailsActivity.class); // Define intent for DetailsActivity
                        detailsIntent.putExtra("locationName", locationName); // Pass data to DetailsActivity - location name
                        startActivity(detailsIntent); // Start DetailsActivity (transition)
                    }
                });

                // Handle "Show Map" button click --> Weather Activity
                showMapButton.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Intent mapIntent = new Intent(MainActivity.this, MapActivity.class); // Define intent for MapActivity
                        mapIntent.putExtra("locationName", locationName); // Pass location name to MapActivity
                        startActivity(mapIntent); // Start MapActivity (transition)
                    }
                });

                return view;
            }
        };
        locationListView.setAdapter(locationAdapter); // Set the adapter

        // On click listener for clicking on adding a location
        addLocationButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Code to add a new location to the list
                showAddLocationDialog(); // Call to bring up dialogue to input and add location
            }
        });

        // Add button to transition to profile page (change UI, log out, view user information
        Button buttonProfileActivity = findViewById(R.id.buttonProfileActivity);
        buttonProfileActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent profileIntent = new Intent(MainActivity.this, ProfileActivity.class); // Define intent for ProfileActivity
                startActivity(profileIntent); // Start ProfileActivity
            }
        });

    } // End of onCreate method

    // onResume method to always keep the local list of locations updated by retrieving from firestore
    protected void onResume() {
        super.onResume();
//        retrieveAndSetVisualPreference();
        updateLocationsFromFirestore();
    }

    // Retrieve UI mode preference from Firestore and set it accordingly in the app
    private void retrieveAndSetVisualPreference() {
        FirebaseAuth mAuth = FirebaseAuth.getInstance(); // Get authentication instance (this is outside of onCreate method
        FirebaseUser user = mAuth.getCurrentUser(); // Get current user
        // If there exists a user
        if (user != null) {
            String userID = user.getUid(); // Get unique user ID
            /*Get this specific document where the preference for UI is stored (this is created if it does not exist)
                Essentially, we are accounting for the fact that it could be a new user and default UI to light mode
                Exiting logic leaves in light mode, which is the default layout of the application
             */
            DocumentReference visualModeDoc = firestore.collection("users").document(userID)
                    .collection("VisualPreference").document("visual_mode");

            // Get information from the document as defined above
            visualModeDoc.get()
                    .addOnSuccessListener(documentSnapshot -> {
                        int newNightMode = AppCompatDelegate.MODE_NIGHT_NO; // Default to light mode

                        // Checking if the document exists
                        if (documentSnapshot.exists()) {
                            // Get the preference for light/dark mode
                            Boolean currentDarkModeEnabled = documentSnapshot.getBoolean("darkModeEnabled");
                            // Below condition checks that the preference exists and what it is (true = dark, false = light)
                            if (currentDarkModeEnabled != null && currentDarkModeEnabled) {
                                // Dark mode enabled preference is Yes/True - store the preference in a new variable to use for comparison
                                newNightMode = AppCompatDelegate.MODE_NIGHT_YES;
                            }
                        }

                        // Check what the current UI mode is (we don't want to execute the above logic every time as this is called in onCreate
                        int currentNightMode = getResources().getConfiguration().uiMode & Configuration.UI_MODE_NIGHT_MASK;

                        // Make the comparison so that we don't execute this method's logic every time due to onCreate
                        if (currentNightMode != newNightMode) {
                            AppCompatDelegate.setDefaultNightMode(newNightMode); // Set the new visual mode
                        }
                    })
                    .addOnFailureListener(e -> {
                        Log.e("Firestore", "Error retrieving preference from Firestore", e); // Error handling
                    });
        }
    }

    // This method saves an added location to Firestore - Firebase's NoSQL database
    private void addLocationToFirestore(String locationName) {
        FirebaseUser user = FirebaseAuth.getInstance().getCurrentUser(); // Get the user who is logged in (Firebase)
        // Check if there is an active user
        if (user != null) {
            String userID = user.getUid(); // Get user's unique user ID
            // Define the document and collection where we save the location information for each
            firestore.collection("users").document(userID).collection("locations")
                    // Add a new HashMap data structure containing the location name, this is so that we can store more information here if we need to
                    .add(new HashMap<String, Object>() {{
                        put("name", locationName); // Save locationName to "name" in the collection
                         }})
                    .addOnSuccessListener(documentReference -> {
                        updateLocationsFromFirestore(); // Call update method so that we can dynamically visualize the list
                    })
                    .addOnFailureListener(e -> {
                        Log.e("Firestore", "Error adding location name to Firestore", e); // Error handling
                    });
        }
    }

    // Retrieve the locations saved for the specific user to be saved and displayed
    private void updateLocationsFromFirestore() {
        FirebaseUser user = FirebaseAuth.getInstance().getCurrentUser(); // Get active user
        // If there exists an active user
        if (user != null) {
            String userID = user.getUid(); // Get user's unique user ID
            firestore.collection("users").document(userID).collection("locations")
                    .get()
                    .addOnSuccessListener(queryDocumentSnapshots -> {
                        locations.clear(); // Clear local list
                        // Loop through each item in the specific document
                        for (QueryDocumentSnapshot document : queryDocumentSnapshots) {
                            String locationName = document.getString("name"); // Get the location name
                            if (locationName != null) {
                                locations.add(locationName); // Add location name to the array of locations
                            }
                        }
                        locationAdapter.notifyDataSetChanged(); // Update the UI with new data (locations)
                    })
                    .addOnFailureListener(e -> {
                        Log.e("Firestore", "Error updating locations from Firestore", e); // Error handling
                    });
        }
    }

    // Method to handle removal of a location - we want to remove it from Firestore as well
    private void removeLocationFromFirestore(String locationName) {
        FirebaseUser user = FirebaseAuth.getInstance().getCurrentUser();
        if (user != null) {
            String userID = user.getUid();
            firestore.collection("users").document(userID).collection("locations")
                    .whereEqualTo("name", locationName)
                    .get()
                    .addOnSuccessListener(queryDocumentSnapshots -> {
                        for (QueryDocumentSnapshot document : queryDocumentSnapshots) {
                            document.getReference().delete()
                                    .addOnSuccessListener(aVoid -> {
                                        updateLocationsFromFirestore(); // Refresh list after location is deleted
                                    })
                                    .addOnFailureListener(e -> {
                                        Log.e("Firestore", "Error deleting from Firestore", e);
                                    });
                        }
                    })
                    .addOnFailureListener(e -> {
                        Log.e("Firestore", "Error querying Firestore to remove location", e);
                    });
        }
    }

    // Method to show dialogue where user will input a location to be added/removed
    private void showAddLocationDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this); // Create builder for the dialogue
        builder.setTitle("Add or delete Location"); // Set dialogue title

        final EditText input = new EditText(this); // Input text
        builder.setView(input); // Have the builder set the view with the input text as an argument

        // The positive case that the user can select - case where user adds the input location
        builder.setPositiveButton("Add", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                String cityName = input.getText().toString().trim(); // Get city/location name
                // Ensure input text is not an empty string
                if (!cityName.isEmpty()) {
                    addLocationToFirestore(cityName); // Add entered location to Firestore (DB)
                }
            }
        });
        // The negative case that the user can select - case where user deletes the input location
        builder.setNegativeButton("Delete", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                String cityName = input.getText().toString().trim();
                // Ensure input text is not an empty string
                if (!cityName.isEmpty()) {
                    removeLocationFromFirestore(cityName); // Remove location from Firestore (DB)
                }
            }
        });

        // The neutral case that the user can select - case where user cancels addition/removal process
        builder.setNeutralButton("Cancel", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.cancel(); // Cancel out of the dialogue
            }
        });

        builder.show();
    }

}

