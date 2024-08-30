package org.jsoup.mytests;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class ManualTest {
    @Test public void testSetHtmlTitle() {
        Document doc = Jsoup.parse("<html><head id=2><title id=1></title></head></html>");

        Element title = doc.getElementById("1");
        title.html("good");
        assertEquals("good", title.html());
        title.html("<i>bad</i>");
        assertEquals("&lt;i&gt;bad&lt;/i&gt;", title.html());

        Element head = doc.getElementById("2");
        head.html("<title><i>bad</i></title>");
        assertEquals("<title>&lt;i&gt;bad&lt;/i&gt;</title>", head.html());
    }

    @Test public void testSetHtmlScript() {
        Document doc = Jsoup.parse("<html><head id=2><title></title></head><script id = 1></script></html>");

        Element script = doc.getElementById("1");
        script.html("let i = 0;");
        assertEquals("let i = 0;", script.html());
    }

    @Test public void testSetHtmlNoScript() {
        Document doc = Jsoup.parse("<html><head id=2><title></title></head><noscript id = 1></noscript></html>");

        Element script = doc.getElementById("1");
        script.html("Your browser does not support JavaScript!");
        assertEquals("Your browser does not support JavaScript!", script.html());
    }

    @Test public void testSetHtmlPlainText() {
        Document doc = Jsoup.parse("<html><head id=2><title></title></head><plaintext id = 1></plaintext></html>");

        Element script = doc.getElementById("1");
        script.html("Welcome!");
        assertEquals("Welcome!", script.html());
    }

    @Test public void testSetHtmlNoEmbed() {
        Document doc = Jsoup.parse("<html><head id=2><title></title></head><embed><noembed id = 1></noembed></embed></html>");

        Element script = doc.getElementById("1");
        script.html("<h1>Alternative content</h1>");
        assertEquals("&lt;h1&gt;Alternative content&lt;/h1&gt;", script.html());
    }
}
