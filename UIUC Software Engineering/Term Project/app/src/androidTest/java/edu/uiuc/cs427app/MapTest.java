package edu.uiuc.cs427app;

import static androidx.test.espresso.Espresso.onView;
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static androidx.test.espresso.matcher.ViewMatchers.isDisplayed;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import static androidx.test.espresso.matcher.ViewMatchers.withText;
import static org.junit.Assert.assertEquals;

import android.os.SystemClock;
import android.view.View;
import android.widget.TextView;

import androidx.annotation.IdRes;
import androidx.test.espresso.Espresso;
import androidx.test.espresso.NoMatchingViewException;
import androidx.test.espresso.ViewAssertion;
import androidx.test.espresso.action.ViewActions;
import androidx.test.espresso.matcher.ViewMatchers;
import androidx.test.ext.junit.runners.AndroidJUnit4;
import androidx.test.rule.ActivityTestRule;

import org.hamcrest.Matchers;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class)
public class MapTest {

    // Assuming LoginActivity is the activity where you perform user login
    @Rule
    public ActivityTestRule<LoginActivity> loginActivityRule = new ActivityTestRule<>(LoginActivity.class);

    @Test
    public void testLoginAndViewMapDetails() {
        // Replace R.id.editTextUsername, R.id.editTextPassword, and R.id.buttonLogin
        // with your actual resource IDs for the username, password, and login button.

        // Type the username and password
        onView(withId(R.id.inputUser)).perform(ViewActions.typeText("urahman2"));
        onView(withId(R.id.inputPassword)).perform(ViewActions.typeText("testPass"));

        // Close the keyboard (if it's open)
        Espresso.closeSoftKeyboard();

        // Click on the login button
        onView(ViewMatchers.withId(R.id.buttonlogin)).perform(ViewActions.click());

        // Wait for the login to complete (you might need to add some synchronization here)
        SystemClock.sleep(4000);

        onView(withId(R.id.locationNameTextView)).perform();
        String cityName = "Chicago";

        // Perform a click on the "Show Weather" button for the specified city

        Espresso.onData(Matchers.is(cityName))
                .inAdapterView(ViewMatchers.withId(R.id.locationListView))
                .onChildView(withId(R.id.showMapButton))
                .perform(ViewActions.click());
        SystemClock.sleep(4000);

        //Assert Block
        //Welcome Text Assert
        onView(withId(R.id.mapTitle)).check(matches(withText("Map of Chicago")));

        String text = getTextFromTextView(R.id.latlong);

        String[] testing = text.split(" ");

        assertEquals(testing[0].split(":")[0], "Lat");
        assertEquals(testing[2].split(":")[0], "Lon");

        Espresso.pressBack();

        cityName = "New York";

        Espresso.onData(Matchers.is(cityName))
                .inAdapterView(ViewMatchers.withId(R.id.locationListView))
                .onChildView(withId(R.id.showMapButton))
                .perform(ViewActions.click());
        SystemClock.sleep(4000);

        //Asset block
        //Welcome Text Assert
        onView(withId(R.id.mapTitle)).check(matches(withText("Map of New York")));

        String text2 = getTextFromTextView(R.id.latlong);

        testing = text2.split(" ");

        assertEquals(testing[0].split(":")[0], "Lat");
        assertEquals(testing[2].split(":")[0], "Lon");

    }

    private String getTextFromTextView(@IdRes int textViewId) {
        final String[] text = {null};

        onView(withId(textViewId))
                .check(matches(isDisplayed()))
                .check(new ViewAssertion() {
                    @Override
                    public void check(View view, NoMatchingViewException noViewFoundException) {
                        if (view instanceof TextView) {
                            text[0] = ((TextView) view).getText().toString();
                        } else {
                            throw new AssertionError("View is not an instance of TextView");
                        }
                    }
                });

        return text[0];
    }
}


