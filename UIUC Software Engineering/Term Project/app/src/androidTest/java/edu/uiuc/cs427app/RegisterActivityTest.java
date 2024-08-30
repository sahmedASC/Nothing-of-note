package edu.uiuc.cs427app;

import static androidx.test.espresso.action.ViewActions.closeSoftKeyboard;
import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertNotNull;

import android.os.SystemClock;

import androidx.annotation.NonNull;
import androidx.test.espresso.Espresso;
import androidx.test.espresso.action.ViewActions;
import androidx.test.espresso.matcher.ViewMatchers;
import androidx.test.ext.junit.runners.AndroidJUnit4;
import androidx.test.rule.ActivityTestRule;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class)
public class RegisterActivityTest  {

    @Rule
    public ActivityTestRule<RegisterActivity> activityRule = new ActivityTestRule<>(RegisterActivity.class);

    @Test
    public void testRegistrationButton() {
    // Get Firebase Authentication instance
        FirebaseAuth mAuth = FirebaseAuth.getInstance();
        String usr_email = "testuser1@illinois.edu";
        String passwd = "password1";

        mAuth.signInWithEmailAndPassword(usr_email,passwd)
                .addOnCompleteListener(new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        if(task.isSuccessful()){
                            FirebaseUser user = mAuth.getCurrentUser();
                            //Delete user account if exist
                            user.delete();
                        }
                    }
                });

        // Type a valid username, password, and confirm password
        Espresso.onView(ViewMatchers.withId(R.id.inputUser)).perform(ViewActions.typeText("testuser1"), closeSoftKeyboard());
        Espresso.onView(ViewMatchers.withId(R.id.inputPassword)).perform(ViewActions.typeText("password1"), closeSoftKeyboard());
        Espresso.onView(ViewMatchers.withId(R.id.inputConfirmPassword)).perform(ViewActions.typeText("password1"), closeSoftKeyboard());

        // Click on the registration button
        Espresso.onView(ViewMatchers.withId(R.id.RegisterUser)).perform(ViewActions.click());
        SystemClock.sleep(4000);
        //login using new username and password
        Espresso.onView(ViewMatchers.withId(R.id.inputUser)).perform(ViewActions.clearText());
        SystemClock.sleep(400);
        Espresso.onView(ViewMatchers.withId(R.id.inputUser)).perform(ViewActions.typeText("testuser1"), closeSoftKeyboard());
        Espresso.onView(ViewMatchers.withId(R.id.inputPassword)).perform(ViewActions.clearText());
        SystemClock.sleep(400);
        Espresso.onView(ViewMatchers.withId(R.id.inputPassword)).perform(ViewActions.typeText("password1"), closeSoftKeyboard());
        SystemClock.sleep(400);
        Espresso.onView(ViewMatchers.withId(R.id.buttonlogin)).perform(ViewActions.click());

        // Validate Firebase authentication
        FirebaseUser currentUser = mAuth.getCurrentUser();

        assertNotNull(currentUser);
        assertEquals("testuser1", currentUser.getDisplayName());
    }



    // Add more tests as needed
}
