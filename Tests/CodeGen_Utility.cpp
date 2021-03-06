#include "../Tests_Helpers.h"
#include <QUtils/CodeGen/Utility.h>

#include "../Output/SrcTest.cpp"
#include "../Output/SrcTest2.cpp"

#include <map>
#include <math.h>
#include <fstream>
#include <QUtils/String/String.h>
#include <type_traits>


using namespace QUtils::CodeGen;

const std::string srcTestPath = TestValues::OutputPath + "/SrcTest.cpp";
const std::string srcTest2Path = TestValues::OutputPath + "/SrcTest2.cpp";

bool Test_CodeGen_Utility()
{
	{
		EmbeddedData embed;
		embed.setTemplate("#include <sstream>\n"
		                  "#define TESTNS_DEFINED\n"
		                  "namespace TestNS\n"
		                  "{\n"
		                  "\tstd::string helloWorld()\n"
		                  "\t{\n"
		                  "\t\tstd::stringstream ss;\n"
		                  "\t\tss REPLACETHIS;\n"
		                  "\t\treturn ss.str();\n"
		                  "\t}\n"
		                  "}\n");
		embed.setReplace("REPLACETHIS");
		embed.setFormat(" << \"${0}\\n\"");
		
		embed.addItem("Hello,\n world!");
		embed.addItem(4.5);
		
		
		
		#ifdef TESTNS_DEFINED
		static_assert(std::is_same<decltype(TestNS::helloWorld()), std::string>::value, "Incorrect return type!");
		{
			std::stringstream value;
			value << "Hello,\n world!\n" << 4.5 << "\n";
			assert_ex(TestNS::helloWorld() == value.str());
		}
		std::ifstream file(srcTestPath);
		std::stringstream src;
		src << file.rdbuf();
		file.close();
		
		std::stringstream ss;
		embed.write(ss);
		
		if (src.str() != ss.str())
		{
			embed.fileWrite(srcTestPath);
		}
		
		assert_ex(src.str() == ss.str());
		#else
		embed.fileWrite(srcTestPath);
		#endif
		
		embed.write(dout);
		
	}
	
	
	
	
	
	
	{
		Generator gen;
		
		auto preprocDef = StringNode::Create("#define SRCTEST2\n");
		gen.add(preprocDef);
		
		auto inc = IncludeNode::Create("string");
		
		
		auto ns = NamespaceNode::Create("TestNS");
		auto ns2 = NamespaceNode::Create("TestNS2");
		ns->children.push_back(ns2);
		
		
		gen.add(inc);
		gen.add(ns);
		ns2->children.push_back(StringNode::Create("//Hello\n//World!\n//This is a\n//test!\n"));
		
		auto fooBody = FunctionBodyNode::Create();
		
		const std::string fooString = "Hello!\b,\nworld.\b!\tTest\vTest2\n\n\fTest3\a\a\a\n\\Testing!";
		
		auto fooStmtChild = LiteralNode::Create(fooString);
		fooBody->children.push_back(ReturnStatementNode::Create(fooStmtChild));
		
		auto fooFunc = FunctionDeclarationNode::Create("std::string", "foo", fooBody);
		
		ns2->children.push_back(fooFunc);
		
		
		#ifdef SRCTEST2
		assert_ex(TestNS::TestNS2::foo() == fooString);
		dout << "String: " << TestNS::TestNS2::foo() << std::endl;
		#else
		gen.writeToFile(srcTest2Path);
		#endif
		
		
		
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
		
		
		{
			std::stringstream ss;
			gen.generate(ss);
			QUtils::String ss_str = ss.str();
			QUtils::String str = fooFunc->toString(2);
			
			assert_ex(ss_str.contains(str));
			QUtils::String::Trim(str);
			
			assert_ex(str.contains("constexpr "));
			{
				assert_ex(str.contains("const "));
				auto constexprIndex = str.find("constexpr");
				assert_ex(str.find("const", constexprIndex+1) != std::string::npos);
				assert_ex(str.find("const", constexprIndex+1) > str.find(") "));
			}
			assert_ex(str.contains("extern "));
			assert_ex(str.contains("virtual "));
			assert_ex(str.contains(" override"));
			assert_ex(str.find("override") > str.find(") "));
			assert_ex(str.contains(" noexcept"));
			assert_ex(str.contains("volatile "));
			assert_ex(str.contains("mutable "));
			assert_ex(str.contains("thread_local "));
			assert_ex(str.contains("static "));
		}
		
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
		
		
		
		const std::string numFuncName = "numFoo";
		
		auto numFunc = FunctionDeclarationNode::Create("double", numFuncName);
		
		ns2->children.push_back(numFunc);
		auto numBody = FunctionBodyNode::Create();
		numFunc->body = numBody;
		
		double num = 1998777ULL;
		
		numBody->children.push_back(::ReturnStatementNode::Create(LiteralNode::Create(num)));
		
		
		
		#ifdef SRCTEST2
		static_assert(std::is_same<decltype(TestNS::TestNS2::numFoo()), double>::value, "Incorrect type for numFoo()");
		assert_ex(TestNS::TestNS2::numFoo() == num);
		#else
		gen.writeToFile(srcTest2Path);
		#endif
		
		numFunc->templateArguments.push_back(NULL);
		{
			QUtils::String str = numFunc->toString(0);
			assert_ex(str.contains(numFuncName + "<>("));
		}
		
		auto vectorInclude = IncludeNode::Create("vector");
		gen.insert(2, vectorInclude);
		
		
		numFunc->templateArguments.clear();
		
		
		
		auto var = VariableDeclarationNode::Create("std::vector<int>", "x");
		
		auto varInit = InitializerListNode::Create();
		var->assignment = varInit;
		
		for (int i = 0; i < 10; ++i)
		{
			varInit->children.push_back(LiteralNode::Create(i));
		}
		
		ns2->children.push_back(var);
		
		
		
		
		{
			QUtils::String str = var->toString(0);
			assert_ex(str.startsWith("std::vector<int> x = { "));
			assert_ex(str.endsWith(" };\n"));
		}
		
		
		
		
		#ifdef SRCTEST2
		for (int i = 0; i < 10; ++i)
		{
			assert_ex(TestNS::TestNS2::x.at(i) == i);
		}
		
		std::ifstream file(srcTest2Path);
		std::stringstream src;
		src << file.rdbuf();
		file.close();
		
		std::stringstream ss;
		gen.generate(ss);
		
		if (ss.str() != src.str())
		{
			gen.writeToFile(srcTest2Path);
		}
		assert_ex(ss.str() == src.str());
		static_assert(std::is_same<decltype(TestNS::TestNS2::x), std::vector<int>>::value, "Incorrect type for x");
		
		
		#else
		gen.writeToFile(srcTest2Path);
		#endif
		dout << "\n\n\n";
		gen.generate(dout);
		dout << "\n\n\n\n";
		
		
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*{
		const std::string headerPath = TestValues::DataPath + "/RucksackData.h";
		const std::string dataPath = std::string("Tests") + "/RucksackData.cpp";
		const int count = 100000;
		const double space = 10000;
		Generator gen_h;
		Generator gen_cpp;
		gen_h.add(IncludeNode::Create("vector"));
		gen_h.add(IncludeNode::Create("tuple"));
		gen_cpp.add(IncludeNode::Create("vector"));
		gen_cpp.add(IncludeNode::Create("tuple"));
		
		//gen_cpp.add(IncludeNode::Create("../" + headerPath, true));
		
		auto ns = NamespaceNode::Create("RucksackData");
		gen_cpp.add(ns);
		
		std::shared_ptr<VariableDeclarationNode> count_n, space_n;
		{
			count_n = VariableDeclarationNode::Create("int", "count");
			count_n->isConst = true;
			count_n->assignment = LiteralNode::Create(count);
			
			
		}
		
		{
			space_n = VariableDeclarationNode::Create("double", "space");
			space_n->isConst = true;
			space_n->assignment = LiteralNode::Create(space);
			
		}
		
		std::shared_ptr<NamespaceNode> ns_h;
		
		{
			ns->children.push_back(NULL);
			auto com = CommentNode::Create("[(Size, Value)]");
			ns->children.push_back(com);
		}
		
		auto func = FunctionDeclarationNode::Create("const std::vector<std::tuple<double, double>>&", "items");
		ns->children.push_back(func);
		ns_h = ns->copy();
		assert_ex(ns_h != ns);
		assert_ex(ns_h->children.size() == ns->children.size());
		
		ns_h->children.insert(ns_h->children.begin(), count_n);
		ns_h->children.insert(ns_h->children.begin(), space_n);
		
		
		
		
		gen_h.add(ns_h);
		
		auto funcBody = FunctionBodyNode::Create();
		func->body = funcBody;
		
		auto var = VariableDeclarationNode::Create("std::vector<std::tuple<double, double>>", "data");
		var->isStatic = true;
		
		funcBody->children.push_back(var);
		
		auto ret = ReturnStatementNode::Create(StringNode::Create("data"));
		funcBody->children.push_back(ret);
		
		auto data = InitializerListNode::Create();
		dout << "Generating Rucksack values...\n";
		for (int i = 0; i < count; ++i)
		{
			auto tup_n = InitializerListNode::Create();
			
			double wgt_rand = static_cast<double>(rand())/RAND_MAX;
			
			double val_rand = static_cast<double>(rand())/RAND_MAX;
			
			tup_n->children.push_back(LiteralNode::Create(wgt_rand*10));
			tup_n->children.push_back(LiteralNode::Create(val_rand*100));
			
			
			data->children.push_back(tup_n);
		}
		var->assignment = data;
		
		
		
		gen_h.writeToFile(headerPath);
		gen_cpp.writeToFile(dataPath);
		
	}*/
	
	return false;
}