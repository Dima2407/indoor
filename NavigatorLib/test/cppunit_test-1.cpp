//
// Created by kyb on 15.03.17.
//

/*#include "teamcity-cpp/cppunit/teamcity_cppunit.h"

//#include "test1.h"


namespace Navigator {
	namespace Test {
		
		class test1
		{
			
		};
		
	}
}*/




#include <iostream>
#include <stdexcept>

#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>

//#include "teamcity-cpp/cppunit/teamcity_cppunit.h"
#include "teamcity/teamcity_cppunit.h"

#include "rapidjson/rapidjson.h"
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/error/en.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


//using namespace CppUnit;
using namespace std;

class BeaconDataFilesTest : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(BeaconDataFilesTest);

	CPPUNIT_TEST(test_20172402_063151);
	CPPUNIT_TEST(test_20172402_063308);
	CPPUNIT_TEST(testNothing);

	CPPUNIT_TEST_SUITE_END();

public:
	void test_20172402_063151();
	
	void test_20172402_063308() {
		//CPPUNIT_ASSERT_EQUAL(2, 1);
	}
	
	void testNothing() {}
};

void BeaconDataFilesTest::test_20172402_063151()
{
	//cout << endl << "asdsaddasads" << endl;
	using namespace rapidjson;
	// Prepare reader and input stream.
	//Reader reader;
	GenericReader<AutoUTF<unsigned>, UTF8<> > reader;       // CHANGED
	char readBuffer[65536];
	FileReadStream is(stdin, readBuffer, sizeof(readBuffer));
	AutoUTFInputStream<unsigned, FileReadStream> eis(is);   // NEW
	
	// Prepare writer and output stream.
	char writeBuffer[65536];
	FileWriteStream os(stdout, writeBuffer, sizeof(writeBuffer));

#if 1
	// Use the same Encoding of the input. Also use BOM according to input.
	typedef AutoUTFOutputStream<unsigned, FileWriteStream> OutputStream;    // NEW
	OutputStream eos(os, eis.GetType(), eis.HasBOM());                      // NEW
	PrettyWriter<OutputStream, UTF8<>, AutoUTF<unsigned> > writer(eos);     // CHANGED
#else
	// You may also use static bound encoding type, such as output to UTF-16LE with BOM
    typedef EncodedOutputStream<UTF16LE<>,FileWriteStream> OutputStream;    // NEW
    OutputStream eos(os, true);                                             // NEW
    PrettyWriter<OutputStream, UTF8<>, UTF16LE<> > writer(eos);             // CHANGED
#endif
	
	// JSON reader parse from the input stream and let writer generate the output.
	//if (!reader.Parse<kParseValidateEncodingFlag>(is, writer)) {
	if (!reader.Parse<kParseValidateEncodingFlag>(eis, writer)) {   // CHANGED
		fprintf(stderr, "\nError(%u): %s\n", static_cast<unsigned>(reader.GetErrorOffset()), GetParseError_En(reader.GetParseErrorCode()));
	}
}



CPPUNIT_TEST_SUITE_REGISTRATION(BeaconDataFilesTest);


/**
 * @brief Run all registered CppUnit tests
 * This version uses either standard (brief+compiler) or TeamCity output
 * @return   0    if success
 */
int main()
{
	//using CppUnit::TestResult;
	//using CppUnit::BriefTestProgressListener;
	using namespace CppUnit;
	
	// Force the teamcity-style output
	constexpr bool FORCE_TEAMCITY = false;
		// Do we use teamcity-style output ?
	bool useTeamcity = JetBrains::underTeamcity() || FORCE_TEAMCITY;
	
	// cout << "Goblins WON !!!" << endl;
	
	// The test results
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