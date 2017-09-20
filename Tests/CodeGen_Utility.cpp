#include "../Tests_Helpers.h"
#include <QUtils/CodeGen/Utility.h>

#include "../SrcTest.cpp"
#include "../SrcTest2.cpp"


bool Test_CodeGen_Utility()
{
	{
		QUtils::CodeGen::EmbeddedData embed;
		embed.setTemplate("#include <iostream>\n"
		                  "#define TESTNS_DEFINED\n"
		                  "namespace TestNS\n"
		                  "{\n"
		                  "\tvoid helloWorld()\n"
		                  "\t{\n"
		                  "\t\tstd::cout REPLACETHIS;\n"
		                  "\t}\n"
		                  "}\n");
		embed.setReplace("REPLACETHIS");
		embed.setFormat(" << \"${0}\\n\"");
		
		embed.addItem("Hello,\n world!");
		embed.addItem(4.5);
		
		embed.fileWrite("SrcTest.cpp");
		#ifdef TESTNS_DEFINED
		TestNS::helloWorld();
		#endif
		
	}
	
	
	
	
	
	
	{
		QUtils::CodeGen::Generator gen;
		
		//auto inc = std::make_shared<QUtils::CodeGen::IncludeNode>("string");
		auto inc = QUtils::CodeGen::IncludeNode::Create("string");
		
		dout << inc->toString(0) << "\n";
		
		//auto ns = std::make_shared<QUtils::CodeGen::NamespaceNode>("TestNS");
		auto ns = QUtils::CodeGen::NamespaceNode::Create("TestNS");
		//auto ns2 = std::make_shared<QUtils::CodeGen::NamespaceNode>("TestNS2");
		auto ns2 = QUtils::CodeGen::NamespaceNode::Create("TestNS2");
		ns->children.push_back(ns2);
		
		dout << ns->toString(0) << "\n";
		
		gen.add(inc);
		gen.add(ns);
		//ns2->children.push_back(std::make_shared<QUtils::CodeGen::StringNode>("//Hello\n//World!\n//This is a\n//test!\n"));
		ns2->children.push_back(QUtils::CodeGen::StringNode::Create("//Hello\n//World!\n//This is a\n//test!\n"));
		
		auto fooBody = QUtils::CodeGen::FunctionBodyNode::Create();
		
		const std::string fooString = "Hello world!";
		
		auto fooStmtChild = QUtils::CodeGen::StringNode::Create("\"" + fooString + "\"");
		fooBody->children.push_back(QUtils::CodeGen::ReturnStatementNode::Create(fooStmtChild));
		
		auto fooFunc = QUtils::CodeGen::FunctionDeclarationNode::Create("std::string", "foo", fooBody);
		
		ns2->children.push_back(fooFunc);
		
		dout << "\n\n";
		gen.generate(dout);
		
		gen.writeToFile("SrcTest2.cpp");
		
		assert_ex(TestNS::TestNS2::foo() == fooString);
		
	}
	
	return true;
}