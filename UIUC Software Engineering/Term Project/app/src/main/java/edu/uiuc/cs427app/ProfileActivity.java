package edu.uiuc.cs427app;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;

import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.os.Bundle;
import android.os.SystemClock;
import android.util.Patterns;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import android.util.Log;
import com.google.firebase.FirebaseApp;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.AuthResult;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.firestore.CollectionReference;
import com.google.firebase.firestore.DocumentReference;
import com.google.firebase.firestore.FirebaseFirestore;

import java.util.HashMap;
import java.util.Map;


public class ProfileActivity extends AppCompatActivity implements View.OnClickListener{

    //Kaiwen
    private boolean isDarkModeEnabled = false;
    private static final String PREFS_NAME = "user_preferences";
    private static final String DARK_MODE_PREF = "dark_mode";
    private static final String LAYOUT_PREF = "user_layout";
    //End Kaiwen


    // Firestore initialization
    private FirebaseFirestore firestore = FirebaseFirestore.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);

        // Set visual mode based on preference from firestore
//        retrieveAndSetVisualPreference();

        // Retrieve username to display on banner
        FirebaseAuth mAuth = FirebaseAuth.getInstance();
        FirebaseUser user = mAuth.getCurrentUser();
        String username = "";
        if (user != null) {
            username += user.getDisplayName();
        }

        // Display correct banner details
        setTitle(getString(R.string.app_name,username));

        // Add button to transition to profile page (change UI, log out, view user information
        Button buttonMainActivity = findViewById(R.id.buttonMainActivity);
        buttonMainActivity.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent mainIntent = new Intent(ProfileActivity.this, MainActivity.class);
                startActivity(mainIntent);
            }
        });
      // Log out button functionality
        Button buttonLogOut = findViewById(R.id.buttonLogOut);
        buttonLogOut.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Sign out the user
                mAuth.signOut();

                // Transition back to LoginActivity
                Intent loginIntent = new Intent(ProfileActivity.this, LoginActivity.class);
                startActivity(loginIntent);
                finish();  // Close the profile activity
            }
        });

        Button buttonToggleDarkMode = findViewById(R.id.buttonChangeVisualMode);
        buttonToggleDarkMode.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {
                updateDarkModePreferenceInFirestore();
                setDarkMode();
            }
        });
    }

//    protected void onResume() {
//        super.onResume();
//        retrieveAndSetVisualPreference();
//    }


    private void setDarkMode() {
        int currentNightMode = getResources().getConfiguration().uiMode & Configuration.UI_MODE_NIGHT_MASK;
        int newNightMode = (currentNightMode == Configuration.UI_MODE_NIGHT_NO) ?
                AppCompatDelegate.MODE_NIGHT_YES : AppCompatDelegate.MODE_NIGHT_NO;
        AppCompatDelegate.setDefaultNightMode(newNightMode);
        recreate(); // Recreate the activity
    }

    private void updateDarkModePreferenceInFirestore() {
        FirebaseAuth mAuth = FirebaseAuth.getInstance();
        FirebaseUser user = mAuth.getCurrentUser();
        if (user != null) {
            String userID = user.getUid();
            DocumentReference userRef = firestore.collection("users").document(userID);
            CollectionReference userVisualPreference = userRef.collection("VisualPreference");

            userVisualPreference.document("visual_mode")
                    .get()
                    .addOnSuccessListener(documentSnapshot -> {
                        Boolean currentDarkModeEnabled = documentSnapshot.getBoolean("darkModeEnabled");

                        // Default if this doesn't exist for the user in firestore already
                        Boolean newDarkModeState = currentDarkModeEnabled != null ? !currentDarkModeEnabled : true;

                        // Update the preference in Firestore
                        Map<String, Object> darkModeUpdate = new HashMap<>();
                        darkModeUpdate.put("darkModeEnabled", newDarkModeState);

                        userVisualPreference.document("visual_mode")
                                .set(darkModeUpdate)
                                .addOnSuccessListener(aVoid -> {
                                    // Preference was successfully updated in Firestore
                                })
                                .addOnFailureListener(e -> {
                                    Log.e("Firestore", "Error updating preference in Firestore", e);
                                });
                    })
                    .addOnFailureListener(e -> {
                        Log.e("Firestore", "Error retrieving preference from Firestore", e);
                    });
        }
    }


    @Override
    public void onClick(View view) {

    }
}
