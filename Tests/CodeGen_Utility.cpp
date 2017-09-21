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
		
		auto preprocDef = QUtils::CodeGen::StringNode::Create("#define SRCTEST2\n");
		gen.add(preprocDef);
		
		auto inc = QUtils::CodeGen::IncludeNode::Create("string");
		
		dout << inc->toString(0) << "\n";
		
		auto ns = QUtils::CodeGen::NamespaceNode::Create("TestNS");
		auto ns2 = QUtils::CodeGen::NamespaceNode::Create("TestNS2");
		ns->children.push_back(ns2);
		
		dout << ns->toString(0) << "\n";
		
		gen.add(inc);
		gen.add(ns);
		ns2->children.push_back(QUtils::CodeGen::StringNode::Create("//Hello\n//World!\n//This is a\n//test!\n"));
		
		auto fooBody = QUtils::CodeGen::FunctionBodyNode::Create();
		
		const std::string fooString = "Hello!\b,\nworld.\b!\tTest\vTest2\n\n\fTest3\a\a\a\n\\Testing!";
		
		auto fooStmtChild = QUtils::CodeGen::LiteralNode::Create(fooString);
		fooBody->children.push_back(QUtils::CodeGen::ReturnStatementNode::Create(fooStmtChild));
		
		auto fooFunc = QUtils::CodeGen::FunctionDeclarationNode::Create("std::string", "foo", fooBody);
		
		ns2->children.push_back(fooFunc);
		
		dout << "\n\n";
		gen.generate(dout);
		
		gen.writeToFile("SrcTest2.cpp");
		#ifdef SRCTEST2
		assert_ex(TestNS::TestNS2::foo() == fooString);
		#endif
		
		dout << "String: " << TestNS::TestNS2::foo() << std::endl;
		
		fooFunc->isConst = true;
		fooFunc->isConstexpr = true;
		fooFunc->isExtern = true;
		fooFunc->isVirtual = true;
		fooFunc->isOverride = true;
		fooFunc->isNoExcept = true;
		fooFunc->isVolatile = true;
		fooFunc->isMutable = true;
		fooFunc->isThread_Local = true;
		fooFunc->isStatic = true;
		
		
		gen.generate(dout);
		
		fooFunc->isConst = false;
		fooFunc->isConstexpr = false;
		fooFunc->isExtern = false;
		fooFunc->isVirtual = false;
		fooFunc->isOverride = false;
		fooFunc->isNoExcept = false;
		fooFunc->isVolatile = false;
		fooFunc->isMutable = false;
		fooFunc->isThread_Local = false;
		fooFunc->isStatic = false;
		
		
		
		auto numFunc = QUtils::CodeGen::FunctionDeclarationNode::Create("double", "numFoo");
		
		ns2->children.push_back(numFunc);
		auto numBody = QUtils::CodeGen::FunctionBodyNode::Create();
		numFunc->body = numBody;
		
		double num = 1998777ULL;
		
		numBody->children.push_back(QUtils::CodeGen::ReturnStatementNode::Create(QUtils::CodeGen::LiteralNode::Create(num)));
		
		gen.generate(dout);
		gen.writeToFile("srcTest2.cpp");
		
		#ifdef SRCTEST2
		assert_ex(TestNS::TestNS2::numFoo() == num);
		#endif
	}
	
	return false;
}