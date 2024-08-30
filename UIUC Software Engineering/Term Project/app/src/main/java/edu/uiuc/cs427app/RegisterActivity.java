package edu.uiuc.cs427app;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
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
import com.google.firebase.auth.UserProfileChangeRequest;

public class RegisterActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        // Initialize FirebaseAuth/authentication instance
        FirebaseAuth mAuth = FirebaseAuth.getInstance();

        TextView username = findViewById(R.id.inputUser);
        TextView password = findViewById(R.id.inputPassword);
        TextView confirm_password = findViewById(R.id.inputConfirmPassword);
        Button register_button = (Button)findViewById(R.id.RegisterUser);

        TextView btn = findViewById(R.id.accountExist);
        btn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v){
                //On click on Login TextView close RegisterActivity
                finish();
            }
        });

        register_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String usr         = new String(username.getText().toString());
                String usr_email = usr + "@illinois.edu";
                String passwd            = new String(password.getText().toString());
                String confirm_passwd    = new String(confirm_password.getText().toString());

                if(!passwd.equals(confirm_passwd) || usr_email.isEmpty() ||
                     usr_email.isEmpty() || passwd.isEmpty() || confirm_passwd.isEmpty())
                {
                    Toast.makeText(RegisterActivity.this,
                            "Registration Failed! Check Your Input or Passwords",
                            Toast.LENGTH_SHORT).show();
                }

                else
                {
                    // Use Firebase Authentication to create/register a new user account
                    mAuth.createUserWithEmailAndPassword(usr_email, passwd)
                            .addOnCompleteListener(RegisterActivity.this, new OnCompleteListener<AuthResult>() {
                                @Override
                                public void onComplete(@NonNull Task<AuthResult> task) {
                                    if (task.isSuccessful()) {
                                        // Successful registration

                                        // Following builder sets DisplayName for the registered user's account, this only needs to occur once
                                        UserProfileChangeRequest profileUpdates = new UserProfileChangeRequest.Builder()
                                                .setDisplayName(usr)
                                                .build();

                                        FirebaseUser user = mAuth.getCurrentUser(); // Get the user who registered
                                        user.updateProfile(profileUpdates); // Update profile to set DisplayName (call the builder)

                                        Toast.makeText(RegisterActivity.this, "Registration Successful! Please Log In.",
                                                Toast.LENGTH_SHORT).show(); // Successful registration pop-up

                                        // Transition to LoginActivity
                                        Intent loginIntent = new Intent(RegisterActivity.this, LoginActivity.class);
                                        startActivity(loginIntent); // Start LoginActivity

                                        finish(); // Close the registration activity
                                    } else {
                                        // Registration failed - Error handling
                                        Toast.makeText(RegisterActivity.this, "Registration Failed!",
                                                Toast.LENGTH_SHORT).show();
                                        String errorMessage = task.getException().getMessage(); // Get error message
                                        Log.e("Firebase Error", errorMessage); // Log error message
                                    }
                                }
                            });
                }

            }
        });

    }
}