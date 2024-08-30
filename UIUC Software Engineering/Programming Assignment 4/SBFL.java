package edu.illinois.cs.debugging;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.parser.Parser;
import org.jsoup.select.Elements;

/**
 * Implementation for Spectrum-based Fault Localization (SBFL).
 *
 */
public class SBFL
{

	/**
	 * Use Jsoup to parse the coverage file in the XML format.
	 * 
	 * @param file
	 * @return a map from each test to the set of lines that it covers
	 * @throws FileNotFoundException
	 * @throws IOException
	 */
	protected static Map<String, Set<String>> readXMLCov(File file)
			throws FileNotFoundException, IOException {
		FileInputStream fileInputStream = new FileInputStream(file);

		Map<String, Set<String>> res = new HashMap<String, Set<String>>();
		Document document = Jsoup.parse(fileInputStream, "UTF-8", "",
				Parser.xmlParser());

		Elements tests = document.select("test");
		for (Element test : tests) {
			Element name = test.child(0);
			Element covLines = test.child(1);

			Set<String> lines = new HashSet<String>();
			String[] items = covLines.text().split(", ");
			Collections.addAll(lines, items);
			res.put(name.text(), lines);
		}
		return res;
	}

	/**
	 * Compute the suspiciousness values for all covered statements based on
	 * Ochiai
	 * 
	 * @param cov
	 * @param failedTests
	 * @return a map from each line to its suspiciousness value
	 */
	public static Map<String, Double> Ochiai(Map<String, Set<String>> cov,
			Set<String> failedTests) {
		// using LinkedHashMap so that the statement list can be ranked
		Map<String, Double> susp = new LinkedHashMap<String, Double>();
		// TODO

		//gather all the statements
		Set<String> statements = new HashSet<>();
		for(String s : cov.keySet()){
			statements.addAll(cov.get(s));
		}

		//run ochiai for every statement
		for (String s : statements){
			int fail = 0;
			int pass = 0;
			//run through all tests
			for (String key : cov.keySet()) {
				//if a test contains a line then check if it's failed test
				//if not it's a passed test
				if (cov.get(key).contains(s)) {
					if (failedTests.contains(key)) {
						fail++;
					} else {
						pass++;
					}
				}

				//do ochicai math
				Double total_fail = (double) failedTests.size();
				Double temp = fail / Math.sqrt(total_fail * (fail + pass));
				susp.put(s, temp);
			}
		}
		return susp;
	}

	/**
	 * Get the suspiciousness value for the buggy line from the suspicious
	 * statement list
	 * 
	 * @param susp
	 * @param buggyLine
	 * @return the suspiciousness value for the buggy line
	 */
	protected static double getSusp(Map<String, Double> susp,
			String buggyLine) {
		return susp.get(buggyLine);
	}

	/**
	 * Rank all statements based on the descending order of their suspiciousness
	 * values. Get the rank (print the lowest rank for the tied cases) for the
	 * buggy line from the suspicious statement list
	 * 
	 * @param susp
	 * @param buggyLine
	 * @return the rank of the buggy line
	 */
	protected static int getRank(Map<String, Double> susp, String buggyLine) {
		List<Map.Entry<String, Double>> list = new LinkedList<Map.Entry<String, Double>>(
				susp.entrySet());
		// TODO
		list.sort(new Comparator<Map.Entry<String, Double>>() {
			@Override
			public int compare(Map.Entry<String, Double> o1, Map.Entry<String, Double> o2) {
				return o1.getValue().compareTo(o2.getValue());
			}
		});
		Collections.reverse(list);

		Double suspVal = susp.get(buggyLine);

		int rank = 0;
		while (true){
			if(rank == list.size()){
				break;
			}
			Map.Entry<String, Double> temp = list.get(rank);
			if(temp.getValue().compareTo(suspVal)<0){
				break;
			}
			rank++;
		}
		return rank;
	}

}
