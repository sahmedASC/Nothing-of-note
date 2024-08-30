package edu.uiuc.cs427app;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertNotNull;

import androidx.test.espresso.Espresso;
import androidx.test.espresso.action.ViewActions;
import androidx.test.espresso.matcher.ViewMatchers;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.ext.junit.runners.AndroidJUnit4;
import androidx.test.filters.LargeTest;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

@LargeTest
@RunWith(AndroidJUnit4.class)
public class CityTest {
    @Rule
    public ActivityScenarioRule<LoginActivity> mActivityScenarioRule =
            new ActivityScenarioRule<>(LoginActivity.class);

    @Test
    public void cityActivityTest() {
        FirebaseAuth mAuth = FirebaseAuth.getInstance();
        Espresso.onView(ViewMatchers.withId(R.id.inputUser)).perform(ViewActions.typeText("testuser1"));
        Espresso.onView(ViewMatchers.withId(R.id.inputPassword)).perform(ViewActions.typeText("password1"));
        Espresso.onView(ViewMatchers.withId(R.id.buttonlogin)).perform(ViewActions.click());
        FirebaseUser currentUser = mAuth.getCurrentUser();

        assertNotNull(currentUser);
        assertEquals("testuser1", currentUser.getDisplayName());
    }
}
