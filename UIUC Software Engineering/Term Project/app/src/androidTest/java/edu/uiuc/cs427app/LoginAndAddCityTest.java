package edu.uiuc.cs427app;

import static junit.framework.TestCase.assertEquals;

import android.os.SystemClock;
import android.widget.EditText;

import androidx.test.espresso.Espresso;
import androidx.test.espresso.action.ViewActions;
import androidx.test.espresso.assertion.ViewAssertions;
import androidx.test.espresso.matcher.ViewMatchers;
import androidx.test.ext.junit.runners.AndroidJUnit4;
import androidx.test.rule.ActivityTestRule;

import org.hamcrest.Matchers;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class)
public class LoginAndAddCityTest {

    // Assuming LoginActivity is the activity where you perform user login
    @Rule
    public ActivityTestRule<LoginActivity> loginActivityRule = new ActivityTestRule<>(LoginActivity.class);

    @Test
    public void testLoginAndAddOrRemoveCity() {
        // Replace R.id.editTextUsername, R.id.editTextPassword, and R.id.buttonLogin
        // with your actual resource IDs for the username, password, and login button.

        // Type the username and password
        Espresso.onView(ViewMatchers.withId(R.id.inputUser)).perform(ViewActions.typeText("urahman2"));
        Espresso.onView(ViewMatchers.withId(R.id.inputPassword)).perform(ViewActions.typeText("testPass"));

        // Close the keyboard (if it's open)
        Espresso.closeSoftKeyboard();

        // Click on the login button
        Espresso.onView(ViewMatchers.withId(R.id.buttonlogin)).perform(ViewActions.click());

        // Wait for the login to complete (you might need to add some synchronization here)
        SystemClock.sleep(4000);
        String cityName = "Beijing";
        boolean cityExists = checkIfCityExists(cityName);
        if(cityExists)
        {
            Espresso.onView(ViewMatchers.withId(R.id.addLocationButton)).check(ViewAssertions.matches(ViewMatchers.isDisplayed()));
            // After successful login, proceed to add a city
            // Replace R.id.buttonAddCity and R.id.editTextCity with your actual resource IDs

            // Click on the button to add a city
            Espresso.onView(ViewMatchers.withId(R.id.addLocationButton)).perform(ViewActions.click());

            // Type the city name in the EditText
            Espresso.onView(ViewMatchers.withClassName(Matchers.equalTo(EditText.class.getName())))
                    .perform(ViewActions.typeText(cityName));
            // Close the keyboard (if it's open)
            Espresso.closeSoftKeyboard();

            // Click on the confirmation button (assuming it's R.id.buttonConfirm)
            Espresso.onView(ViewMatchers.withText("Delete")).perform(ViewActions.click());
            SystemClock.sleep(400);
            boolean a = checkIfCityExists(cityName);
            assertEquals(a, false);
        }
        else{
            // After successful login, proceed to add a city
            // Replace R.id.buttonAddCity and R.id.editTextCity with your actual resource IDs

            // Click on the button to add a city
            Espresso.onView(ViewMatchers.withId(R.id.addLocationButton)).perform(ViewActions.click());

            // Type the city name in the EditText
            Espresso.onView(ViewMatchers.withClassName(Matchers.equalTo(EditText.class.getName())))
                    .perform(ViewActions.typeText(cityName));
            // Close the keyboard (if it's open)
            Espresso.closeSoftKeyboard();

            // Click on the confirmation button (assuming it's R.id.buttonConfirm)
            Espresso.onView(ViewMatchers.withText("Add")).perform(ViewActions.click());
            SystemClock.sleep(400);

            // Verify that the city is added
            // Replace R.id.textViewCityName with the actual resource ID of the TextView displaying city names
            // Verify that the city is added to the ListView
            // Replace R.id.listViewCities with the actual resource ID of your ListView
            Espresso.onView(ViewMatchers.withId(R.id.locationListView))
                    .check(ViewAssertions.matches(ViewMatchers.hasDescendant(ViewMatchers.withText(cityName))));
            boolean b= checkIfCityExists(cityName);
            assertEquals(b, true);

        }





    }
    private boolean checkIfCityExists(String cityName) {
        try {
            // Assuming R.id.locationListView is the resource ID for your ListView
            Espresso.onData(Matchers.is(cityName))
                    .inAdapterView(ViewMatchers.withId(R.id.locationListView))
                    .check(ViewAssertions.matches(ViewMatchers.isDisplayed()));

            // City found in the ListView
            return true;
        } catch (Exception e) {
            // City not found in the ListView
            return false;
        }
    }
}


