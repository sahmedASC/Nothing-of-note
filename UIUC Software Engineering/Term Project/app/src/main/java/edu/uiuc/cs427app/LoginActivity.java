package edu.uiuc.cs427app;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import com.google.firebase.FirebaseApp;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.AuthResult;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.UserProfileChangeRequest;

public class LoginActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        // Initialize Firebase - this will always be the landing page of the application
        FirebaseApp.initializeApp(this);

        // Initialize FirebaseAuth
        FirebaseAuth mAuth = FirebaseAuth.getInstance();

        TextView signup_text_view = findViewById(R.id.textViewSignUp);
        TextView username = findViewById(R.id.inputUser);
        TextView password = findViewById(R.id.inputPassword);
        Button login_button = (Button)findViewById(R.id.buttonlogin);
        signup_text_view.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                //On click on Sign Up start RegisterActivity
                startActivity(new Intent(LoginActivity.this, RegisterActivity.class));
            }
        });

        login_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final String usr = username.getText().toString(); // Set username
                final String passwd = password.getText().toString(); // Set password
                final String usr_email = usr + "@illinois.edu"; // Appending illinois.edu domain for Firebase authentication

                // Check that username and password inputs are not empty
                if (!usr.isEmpty() && !passwd.isEmpty()) {
                    // Call Firebase sign in with email and password
                    mAuth.signInWithEmailAndPassword(usr_email, passwd)
                            .addOnCompleteListener(LoginActivity.this, new OnCompleteListener<AuthResult>() {
                                @Override
                                public void onComplete(@NonNull Task<AuthResult> task) {
                                    // Login is successful
                                    if (task.isSuccessful()) {
                                        // Builder that sets display name (username) for the user
//                                        UserProfileChangeRequest profileUpdates = new UserProfileChangeRequest.Builder()
//                                                .setDisplayName(usr)
//                                                .build();

                                        FirebaseUser user = mAuth.getCurrentUser();
//                                        user.updateProfile(profileUpdates);

                                        if (user != null) {
                                            Toast.makeText(LoginActivity.this, "Welcome, " + usr_email + "!", Toast.LENGTH_SHORT).show();
                                        }

                                        // Transition to main activity
                                        Intent mainIntent = new Intent(LoginActivity.this, MainActivity.class);
                                        startActivity(mainIntent);

                                        finish(); // Close the login activity
                                    }
                                    // Login failed
                                    else {
                                        Toast.makeText(LoginActivity.this, "Login Failed!", Toast.LENGTH_SHORT).show();
                                    }
                                }
                            });
                }
            }
        });
    }
}