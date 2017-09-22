#include "../Tests_Helpers.h"
#include <QUtils/CodeGen/Utility.h>

#include "../SrcTest.cpp"
#include "../SrcTest2.cpp"

#include <map>
#include <math.h>


using namespace QUtils::CodeGen;

bool Test_CodeGen_Utility()
{
	{
		::EmbeddedData embed;
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
		Generator gen;
		
		auto preprocDef = StringNode::Create("#define SRCTEST2\n");
		gen.add(preprocDef);
		
		auto inc = IncludeNode::Create("string");
		
		dout << inc->toString(0) << "\n";
		
		auto ns = NamespaceNode::Create("TestNS");
		auto ns2 = NamespaceNode::Create("TestNS2");
		ns->children.push_back(ns2);
		
		dout << ns->toString(0) << "\n";
		
		gen.add(inc);
		gen.add(ns);
		ns2->children.push_back(StringNode::Create("//Hello\n//World!\n//This is a\n//test!\n"));
		
		auto fooBody = FunctionBodyNode::Create();
		
		const std::string fooString = "Hello!\b,\nworld.\b!\tTest\vTest2\n\n\fTest3\a\a\a\n\\Testing!";
		
		auto fooStmtChild = LiteralNode::Create(fooString);
		fooBody->children.push_back(ReturnStatementNode::Create(fooStmtChild));
		
		auto fooFunc = FunctionDeclarationNode::Create("std::string", "foo", fooBody);
		
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
		
		
		
		auto numFunc = FunctionDeclarationNode::Create("double", "numFoo");
		
		ns2->children.push_back(numFunc);
		auto numBody = FunctionBodyNode::Create();
		numFunc->body = numBody;
		
		double num = 1998777ULL;
		
		numBody->children.push_back(::ReturnStatementNode::Create(LiteralNode::Create(num)));
		
		gen.generate(dout);
		gen.writeToFile("srcTest2.cpp");
		
		#ifdef SRCTEST2
		assert_ex(TestNS::TestNS2::numFoo() == num);
		#endif
		
		numFunc->templateArguments.push_back(NULL);
		
		auto vectorInclude = IncludeNode::Create("vector");
		gen.insert(2, vectorInclude);
		
		
		gen.generate(dout);
		
		numFunc->templateArguments.clear();
		
		
		
		auto var = VariableDeclarationNode::Create("std::vector<int>", "x");
		
		auto varInit = InitializerListNode::Create();
		var->assignment = varInit;
		
		for (int i = 0; i < 10; ++i)
		{
			varInit->children.push_back(LiteralNode::Create(i));
		}
		
		ns2->children.push_back(var);
		
		gen.generate(dout);
		
		gen.writeToFile("SrcTest2.cpp");
		#ifdef SRCTEST2
		for (int i = 0; i < 10; ++i)
		{
			assert_ex(TestNS::TestNS2::x.at(i) == i);
		}
		#endif
		
	}
	
	/*{
		Generator tsGen;
		
		const int bound = 10;
		const int count = 200;
		
		std::vector<std::tuple<int, int, double>> rawData;
		
		{
			std::map<int, std::tuple<int, int>> points;
			int x, y;
			for (int i = 0; i < count; i++)
			{
				x = (static_cast<double>(rand())/RAND_MAX - 0.5)*2*bound;
				y = (static_cast<double>(rand())/RAND_MAX - 0.5)*2*bound;
				points[i] = std::make_tuple(x, y);
			}
			double dist;
			int x0, y0;
			for (int i = 0; i < count; i++)
			{
				x = std::get<0>(points[i]);
				y = std::get<1>(points[i]);
				for (int j = i+1; j < count; j++)
				{
					x0 = std::get<0>(points[j]);
					y0 = std::get<1>(points[j]);
					dist = sqrt((x - x0)*(x-x0) + (y - y0)*(y - y0));
					rawData.push_back(std::make_tuple(i, j, dist));
				}
			}
		}
		
		std::map<int, std::map<int, double>> edges;
		
		for (auto& e : rawData)
		{
			edges[std::get<0>(e)][std::get<1>(e)] = std::get<2>(e);
		}
		
		
		tsGen.add(IncludeNode::Create("map"));
		tsGen.add(IncludeNode::Create("tuple"));
		
		auto ns = NamespaceNode::Create("TSData");
		
		tsGen.add(ns);
		
		auto countVar = VariableDeclarationNode::Create("int", "count", LiteralNode::Create(count));
		countVar->isConst = true;
		
		ns->children.push_back(countVar);
		
		auto boundVar = VariableDeclarationNode::Create("int", "bound", LiteralNode::Create(bound));
		boundVar->isConst = true;
		ns->children.push_back(boundVar);
		
		auto edgesVar = VariableDeclarationNode::Create("std::map<int, std::map<int, double>>", "edges");
		edgesVar->isConst = true;
		ns->children.push_back(edgesVar);
		
		auto data = InitializerListNode::Create();
		
		edgesVar->assignment = data;
		
		for (auto& city : edges)
		{
			auto cityPair = InitializerListNode::Create();
			data->children.push_back(cityPair);
			cityPair->children.push_back(LiteralNode::Create(city.first));
			auto cityData = InitializerListNode::Create();
			cityPair->children.push_back(cityData);
			for (auto& edge : city.second)
			{
				auto edgeData = InitializerListNode::Create();
				edgeData->children.push_back(LiteralNode::Create(edge.first));
				edgeData->children.push_back(LiteralNode::Create(edge.second));
				cityData->children.push_back(edgeData);
			}
		}
		
		
		tsGen.generate(dout);
		tsGen.writeToFile("Data/TravelingSalesmanData.h");
	}*/
	
	return false;
}