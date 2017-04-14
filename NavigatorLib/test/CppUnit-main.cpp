//
// Created by kyb on 20.03.17.
//


#include <iostream>

//ToDo from official repo in lib/ #include "teamcity-cpp/cppunit/teamcity_cppunit.h"
#include "teamcity/teamcity_cppunit.h"

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace std;


/**
 * @brief Run all registered CppUnit tests
 * This version uses either standard (brief+compiler) or TeamCity output
 * @return   0    if success
 */
int main()
{
	using namespace CppUnit;
	
	// Force the teamcity-style output
	bool FORCE_TEAMCITY = false;
	// Do we use teamcity-style output ?
	bool useTeamcity = JetBrains::underTeamcity() || FORCE_TEAMCITY;
	
	// Create the event manager and test controller
	TestResult result;
	
	// Add either Brief or TeamCity progress listener
	BriefTestProgressListener briefProgress;
	JetBrains::TeamcityProgressListener teamProgress;
	
	if (useTeamcity) {
		result.addListener(&teamProgress);
	} else {
		result.addListener(&briefProgress);
	}
	
	// Add the collector as a listener
	// I don't use collector here much, but it can be useful for various outputs, like XML
	TestResultCollector collector;
	result.addListener(&collector);
	
	// The runner
	TestRunner runner;
	
	// Add all registered tests
	runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
	
	// RUN all tests here
	runner.run(result);
	
	// Output the result with an outputter
	if (!useTeamcity) {
		CompilerOutputter outputter(&collector, cerr);
		outputter.write();
	}
	
	// Return number of failures or 0 if successful
	return collector.testFailures();
}
/*int main(int argc, char **argv)
{
	// Create the event manager and test controller
	TestResult controller;
	
	// Add a listener that collects test result
	TestResultCollector result;
	controller.addListener(&result);
	
	// Add the top suite to the test runner
	TestRunner runner;
	runner.addTest(TestFactoryRegistry::getRegistry().makeTest());
	
	// Listen to progress
	TestListener *listener;
	
	if (jetbrains::teamcity::underTeamcity()) {
		// Add unique flowId parameter if you want to run test processes in parallel
		// See http://confluence.jetbrains.net/display/TCD6/Build+Script+Interaction+with+TeamCity#BuildScriptInteractionwithTeamCity-MessageFlowId
		listener = new jetbrains::teamcity::TeamcityProgressListener();
	} else {
		listener = new BriefTestProgressListener();
	}
	controller.addListener(listener);
	
	// Run tests
	runner.run(controller);
	
	delete listener;
	
	return result.wasSuccessful() ? 0 : 1;
}*/