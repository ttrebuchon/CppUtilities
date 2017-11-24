#include <QUtils/DBC/All.h>

#include "../Tests_Helpers.h"

#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <QUtils/String.h>

struct ForeignKeyData
{
	std::string table, reference;
	size_t column;
};

std::list<std::string> getFilenames();

void findCommonData(const uint num);
std::list<ForeignKeyData> tryFindFKs();
void vtableTesting();

DEF_TEST(DBC)
{
	const std::string filepath = "Test_Files/DBC/Spell.dbc";
	const std::string filepath2 = "Test_Files/DBC/SpellMechanic.dbc";
	const std::string filepath3 = "Test_Files/DBC/Talent.dbc";
	const std::string filepath4 = "Test_Files/DBC/TalentTab.dbc";
	const std::string filepath5 = "Test_Files/DBC/StringLookups.dbc";
	
	
	QUtils::Dbc::DbcFile spell(filepath.c_str());
	
	
	dout << "Record Count: " << spell.size() << "\n";
	dout << "Column Count: " << spell.columns() << "\n";
	
	auto r1 = spell[0];
	
	assert_ex(r1.width() == 234);
	dout << "r1 int<0>: " << r1.intAt(0) << "\n";
	dout << r1.at<const char*>(0) << "\n";
	
	
	auto r2 = spell[1];
	
	assert_ex(r2.width() == 234);
	dout << "r2 int<0>: " << r2.intAt(0) << "\n";
	dout << r2.at<const char*>(0) << "\n";
	
	/*for (int i = 0; i < spell.size(); ++i)
	{
		dout << i << ": " << spell.at(i).at<uint>(0) << "\n";
	}*/
	
	std::vector<std::pair<size_t, size_t>> drains;
	
	for (int j = 0; j < spell.size() && j < 500; ++j)
	{
	auto r = spell.at(j);
	for (int i = 0; i < spell.columns(); ++i)
	{
		//dout << j << "-" << i << ": " << r.at<uint>(i) << " | " << r.at<float>(i) << " | " << r.at<int>(i) << "\n";
		if (r.at<int>(i) > 150000 && r.at<int>(i) < 16800000)
		{
			//dout << "\t" << r.at<std::string>(i) << "\n";
			if (r.at<std::string>(i).find("Drain") != std::string::npos)
			{
				dout << "\t" << r.at<std::string>(i) << "\n";
				drains.emplace_back(j, i);
			}
		}
	}
	//dout << "\n\n\n\n";
	}
	
	dout << "\n\n\n\n";
	
	auto imprDrainSoulProc = spell.findRowWithValue(0, 18371);
	auto imprDrainSoulR1 = spell.findRowWithValue(0, 18213);
	
	dout << "Improved Drain Soul Rank 1:\n";
	for (int i = 0; i < imprDrainSoulR1.width(); ++i)
	{
		if (imprDrainSoulR1.couldBeString(i))
		{
			dout << imprDrainSoulR1.at<uint>(i) << " - \"" << imprDrainSoulR1.at<std::string>(i) << "\"\n\n";
		}
		else
		{
			dout << imprDrainSoulR1.at<uint>(i) << " - " << imprDrainSoulR1.at<float>(i) << "\n\n";
		}
	}
	dout << "\n\n\n\n";
	
	
	dout << "Improved Drain Soul Proc:\n";
	for (int i = 0; i < imprDrainSoulProc.width(); ++i)
	{
		if (imprDrainSoulProc.couldBeString(i))
		{
			dout << imprDrainSoulProc.at<uint>(i) << " - \"" << imprDrainSoulProc.at<std::string>(i) << "\"\n\n";
		}
		else
		{
			dout << imprDrainSoulProc.at<uint>(i) << " - " << imprDrainSoulProc.at<float>(i) << "\n\n";
		}
	}
	dout << "\n\n\n\n";
	
	dout << "Max String Index: " << spell.maxStringIndex() << "\n";
	
	
	
	
	dout << "\n\n";
	QUtils::Dbc::DbcFile spellMech(filepath2.c_str());
	
	dout << "Spell Mechanic Rows: " << spellMech.size() << "\n\n";
	
	
	for (auto m : spellMech)
	{
		for (int i = 0; i < m.width(); ++i)
		{
			if (m.couldBeString(i))
			{
				dout << m.at<uint>(0) << " - \"" << m.at<std::string>(i) << "\"\n";
			}
		}
	}
	
	
	
	
	dout << "\n\n";
	QUtils::Dbc::DbcFile talent(filepath3.c_str());
	
	dout << "Talent Rows: " << talent.size() << "\n\n";
	
	
	for (auto t : talent)
	{
		for (int i = 0; i < t.width(); ++i)
		{
			if (t.couldBeString(i))
			{
				dout << t.at<uint>(0) << " - \"" << t.at<std::string>(i) << "\"\n";
			}
		}
	}
	
	
	
	
	auto searchSpell_id = [&](auto id)
	{
		try
		{
			auto x = spell.findRowWithValue<decltype(id)>(0, id);
			typedef decltype(x) X;
			auto ptr = new X(x);
			return ptr;
		}
		catch (...)
		{
			return (QUtils::Dbc::DbcRow*)nullptr;
		}
	};
	
	auto printRowStrings = [](auto& row)
	{
		for (int i = 0; i < row.width(); ++i)
		{
			if (row.couldBeString(i))
			{
				dout << "\"" << (row.template at<std::string>(i)) << "\"\n";
			}
		}
	};
	
	
	{
	auto drainSoul = searchSpell_id(1120);
	assert_ex(drainSoul != NULL);
	printRowStrings(*drainSoul);
	delete drainSoul;
	}
	
	std::list<QUtils::Dbc::DbcRow> shardRows;
	for (auto s : spell)
	{
		for (int i = 0; i < s.width(); ++i)
		{
			if (s.couldBeString(i))
			{
				QUtils::String str = s.at<std::string>(i);
				str = str.toUpper();
				if (str.contains("SOUL SHARD") && str.contains("DRAIN SOUL") && !str.contains("GLYPH"))
				{
					shardRows.push_back(s);
					break;
				}
			}
		}
	}
	
	{
		bool found;
		for (auto it = shardRows.begin(); it != shardRows.end();)
		{
			found = false;
			for (int i = 0; i < it->width() && !found; ++i)
			{
				assert_ex(!found);
				if (it->couldBeString(i))
				{
					QUtils::String str = it->at<std::string>(i);
					str = str.toUpper();
					found = str.contains("GLYPH");
				}
			}
			if (found)
			{
				it = shardRows.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	
	dout << "Shard Rows: \n{\n";
	for (auto& s : shardRows)
	{
		dout << "\t" << s.at<uint>(0) << "\n";
		for (int i = 0; i < s.width(); ++i)
		{
			if (s.couldBeString(i))
			{
				QUtils::String str = s.at<std::string>(i);
				auto uStr = str.toUpper();
				if (uStr.contains("SOUL SHARD") || i == 136 || i == 137)
				{
					dout << "\t\t" << i << " - \"" << str << "\"\n";
				}
			}
			else if (s.at<uint>(i) != 0)
			{
				dout << "\t\t" << i << " - '" << s.at<uint>(i) << "' - '" << s.at<float>(i) << "'\n";
			}
		}
		dout << "\n";
	}
	dout << "}\n";
	
	
	std::list<QUtils::Dbc::DbcRow> drainRows;
	for (auto s : spell)
	{
		if (QUtils::String(s.at<std::string>(136)).toUpper() == "DRAIN SOUL")
		{
			drainRows.push_back(s);
		}
	}
	
	for (int i = 0; i < spell.columns(); ++i)
	{
		if (drainRows.front().couldBeString(i))
		{
			continue;
		}
		if (drainRows.front().at<uint>(i) == 0)
		{
			continue;
		}
		dout << i << " {\n";
		for (auto& s : drainRows)
		{
			dout << "\t" << s.at<uint>(0) << "\t" << s.at<std::string>(136) << "\t\t" << s.at<uint>(i) << "\n";
		}
		dout << "}\n\n";
	}
	
	
	
	std::list<QUtils::Dbc::DbcRow> imprDrain;
	const QUtils::String imprDrainStr = "";
	
	for (auto t : talent)
	{
		for (int i = 0; i < t.width(); ++i)
		{
			if (t.couldBeString(i))
			{
				QUtils::String str = t.at<std::string>(i);
				str = str.toUpper();
				if (str.contains(imprDrainStr.toUpper()))
				{
					imprDrain.push_back(t);
					break;
				}
			}
		}
	}
	
	dout << "Improved Drain Soul Rows: \n{\n";
	for (auto& s : imprDrain)
	{
		dout << "\t" << s.at<uint>(0) << "\n";
		for (int i = 0; i < s.width(); ++i)
		{
			if (s.couldBeString(i))
			{
				QUtils::String str = s.at<std::string>(i);
				auto uStr = str.toUpper();
				if (uStr.contains(imprDrainStr.toUpper()) || i == 136 || i == 137)
				{
					dout << "\t\t" << i << " - \"" << str << "\"\n";
				}
			}
			else if (s.at<uint>(i) != 0)
			{
				dout << "\t\t" << i << " - '" << s.at<uint>(i) << "' - '" << s.at<float>(i) << "'\n";
			}
		}
		dout << "\n";
	}
	dout << "}\n";
	
	
	
	
	dout << "\n\n";
	QUtils::Dbc::DbcFile talentTab(filepath4.c_str());
	
	/*dout << "TalentTab Rows: " << talent.size() << "\n\n";
	
	
	for (auto t : talentTab)
	{
		for (int i = 0; i < t.width(); ++i)
		{
			if (t.couldBeString(i))
			{
				dout << t.at<uint>(0) << "(" << i << ") - \"" << t.at<std::string>(i) << "\"\n";
			}
		}
	}*/
	
	
	
	
	
	std::list<QUtils::Dbc::DbcRow> afflic;
	const QUtils::String afflicStr = "Afflic";
	
	for (auto t : talentTab)
	{
		for (int i = 0; i < t.width(); ++i)
		{
			if (t.couldBeString(i))
			{
				QUtils::String str = t.at<std::string>(i);
				str = str.toUpper();
				if (str.contains(afflicStr.toUpper()))
				{
					afflic.push_back(t);
					break;
				}
			}
		}
	}
	
	dout << "Affliction Rows: \n{\n";
	for (auto& s : afflic)
	{
		dout << "\t" << s.at<uint>(0) << "\n";
		for (int i = 0; i < s.width(); ++i)
		{
			if (s.couldBeString(i))
			{
				QUtils::String str = s.at<std::string>(i);
				dout << "\t\t" << i << " - \"" << str << "\"\n";
			}
			else if (s.at<uint>(i) != 0)
			{
				dout << "\t\t" << i << " - '" << s.at<uint>(i) << "' - '" << s.at<float>(i) << "'\n";
			}
		}
		dout << "\n";
	}
	dout << "}\n";
	
	
	{
	std::vector<std::tuple<uint, uint, uint, uint, uint>> common;
	for (auto t : talent)
	{
		for (auto& tt : afflic)
		{
			for (uint i = 0; i < t.width(); ++i)
			{
				if (t.couldBeString(i))
				{
					continue;
				}
				for (uint j = 0; j < tt.width(); ++j)
				{
					if (tt.couldBeString(j))
					{
						continue;
					}
					auto v1 = t.at<uint>(i);
					if (v1 != 0)
					{
						if (v1 == tt.at<uint>(j))
						{
							common.emplace_back(t.at<uint>(0), tt.at<uint>(0), i, j, v1);
						}
					}
				}
			}
		}
	}
	
	for (auto& c : common)
	{
		dout << "(" << std::get<0>(c) << ", " << std::get<1>(c) << ", " << std::get<2>(c) << ", " << std::get<3>(c) << ", " << std::get<4>(c) << ")\n";
		
	}
	
	}
	
	dout << std::string(40, '_') << std::string(10, '\n');
	findCommonData(1120);
	dout << std::string(40, '_') << std::string(10, '\n');
	tryFindFKs();
	dout << std::string(40, '_') << std::string(10, '\n');
	vtableTesting();
	dout << std::string(40, '_') << std::string(10, '\n');
	
	return true;
}

#include <dirent.h>
#include <map>

void findCommonData(const uint num)
{
	using namespace QUtils::Dbc;
	dout << "findCommonData(" << num << "):\n\n\n";
	
	std::list<std::string> filenames = getFilenames();
	
	std::list<QUtils::Dbc::DbcFile*> files;
	std::map<DbcFile*, std::string> filesToNames;
	for (auto str : filenames)
	{
		std::string strFull = "Test_Files/DBC/" + str;
		try
		{
			files.push_back(new DbcFile(strFull.c_str()));
			filesToNames[files.back()] = str;
		}
		catch (...)
		{
			continue;
		}
	}
	
	std::list<std::pair<QUtils::Dbc::DbcRow, std::string>> rows;
	
	for (auto filePtr : files)
	{
		for (auto r : *filePtr)
		{
			for (int i = 1; i < r.width(); ++i)
			{
				if (r.at<uint>(i) == num)
				{
					rows.emplace_back(r, filesToNames.at(filePtr));
					
					break;
				}
			}
		}
	}
	
	dout << rows.size() << " rows total.\n";
	
	
	std::map<std::string, int> pCount;
	for (auto& rowP : rows)
	{
		if (pCount[rowP.second] >= 100)
		{
			continue;
		}
		dout << rowP.second << "\t(" << rowP.first.at<uint>(0) << ")\n{\n";
		
		for (int i = 0; i < rowP.first.width(); ++i)
		{
			if (rowP.first.couldBeString(i))
			{
				
				dout << "\t(" << i << ") '" << rowP.first.at<std::string>(i) << "'\n";
			}
			else if (rowP.first.at<uint>(i) == num)
			{
				
				dout << "\t(" << i << ") " << rowP.first.at<uint>(i) << "\n";
			}
		}
		dout << "}\n\n";
		++pCount[rowP.second];
	}
	
	
	
	
	
	
	
	
	
	//Cleanup
	
	for (auto file : files)
	{
		delete file;
	}
	files.clear();
	return;
}



#include <set>

std::list<ForeignKeyData> tryFindFKs()
{
	std::list<ForeignKeyData> FKs;
	
	
	using namespace QUtils::Dbc;
	dout << __func__ << ":\n\n\n";
	
	std::list<std::string> filenames = getFilenames();
	
	std::list<QUtils::Dbc::DbcFile*> files;
	std::map<DbcFile*, std::string> filesToNames;
	std::map<std::string, DbcFile*> namesToFiles;
	for (auto str : filenames)
	{
		std::string strFull = "Test_Files/DBC/" + str;
		try
		{
			files.push_back(new DbcFile(strFull.c_str()));
			filesToNames[files.back()] = str;
			namesToFiles[str] = files.back();
		}
		catch (...)
		{
			continue;
		}
	}
	
	
	for (auto it = files.begin(); it != files.end();)
	{
		auto& file = **it;
		if (file.uniqueID())
		{
			++it;
		}
		else
		{
			filesToNames.erase(*it);
			delete *it;
			it = files.erase(it);
		}
	}
	
	/*ForeignKeyData dat;
	
	for (auto filePtr : files)
	{
		if (filesToNames.at(filePtr) != "Spell.dbc")
		{
			continue;
		}
		DbcFile& file = *filePtr;
		assert_ex(file.columns() > 0);
		dat.table = filesToNames.at(filePtr);
		
		for (int i = 1; i < file.columns(); ++i)
		{
			dat.column = i;
			for (auto filePtr2 : files)
			{
				bool found = true;
				bool allZero = true;
				if (filePtr2 == filePtr)
				{
					//continue;
				}
				auto& file2 = *filePtr2;
				
				assert_ex(file2.columns() > 0);
				uint val;
				for (auto r : file)
				{
					try
					{
						val = r.at<uint>(i);
						if (allZero && val != 0)
						{
							allZero = false;
						}
						file2.getById(val);
					}
					catch (...)
					{
						found = false;
						break;
					}
				}
				if (found && !allZero)
				{
					dat.reference = filesToNames.at(filePtr2);
					FKs.push_back(dat);
					//dout << "Found FK\n";
				}
			}
		}
	}
	
	dout << "FKs: " << FKs.size() << "\n";
	
	
	for (const auto& fk : FKs)
	{
		dout << QUtils::String(fk.table).padLeft(1).padRight(30) << "-> " << QUtils::String(fk.column).padRight(3) << " -> " << fk.reference << "\n";
	}
	
	dout << "FKs: " << FKs.size() << "\n";
	*/
	
	auto& spell = *namesToFiles.at("Spell.dbc");
	for (int i = 1; i < spell.columns(); ++i)
	{
		dout << "(" << QUtils::String(i).padRight(3) << " / " << spell.columns() << ") Text? " << (spell.couldBeString(i, false) ? "True" : "False") << "\n";
	}
	
	assert_ex(spell.couldBeString(136));
	assert_ex(spell.couldBeString(137));
	assert_ex(spell.couldBeString(138));
	assert_ex(spell.couldBeString(139));
	assert_ex(spell.couldBeString(140));
	assert_ex(spell.couldBeString(141));
	assert_ex(spell.couldBeString(142));
	assert_ex(spell.couldBeString(143));
	assert_ex(spell.couldBeString(144));
	assert_ex(spell.couldBeString(145, true));
	assert_ex(spell.couldBeString(146, true));
	assert_ex(spell.couldBeString(147, true));
	assert_ex(spell.couldBeString(148, true));
	assert_ex(spell.couldBeString(149, true));
	assert_ex(spell.couldBeString(150, true));
	assert_ex(spell.couldBeString(151, true));
	
	assert_ex(spell.couldBeString(153));
	assert_ex(spell.couldBeString(154));
	assert_ex(spell.couldBeString(155, true));
	assert_ex(spell.couldBeString(156, true));
	assert_ex(spell.couldBeString(157, true));
	assert_ex(spell.couldBeString(158, true));
	assert_ex(spell.couldBeString(159, true));
	assert_ex(spell.couldBeString(160, true));
	assert_ex(spell.couldBeString(161, true));
	assert_ex(spell.couldBeString(162, true));
	assert_ex(spell.couldBeString(163, true));
	assert_ex(spell.couldBeString(164, true));
	assert_ex(spell.couldBeString(165, true));
	assert_ex(spell.couldBeString(166, true));
	assert_ex(spell.couldBeString(167, true));
	assert_ex(spell.couldBeString(168, true));
	
	assert_ex(spell.couldBeString(170));
	assert_ex(spell.couldBeString(171));
	assert_ex(spell.couldBeString(172, true));
	assert_ex(spell.couldBeString(173, true));
	assert_ex(spell.couldBeString(174, true));
	assert_ex(spell.couldBeString(175, true));
	assert_ex(spell.couldBeString(176, true));
	assert_ex(spell.couldBeString(177, true));
	assert_ex(spell.couldBeString(178, true));
	assert_ex(spell.couldBeString(179, true));
	assert_ex(spell.couldBeString(180, true));
	assert_ex(spell.couldBeString(181, true));
	assert_ex(spell.couldBeString(182, true));
	assert_ex(spell.couldBeString(183, true));
	assert_ex(spell.couldBeString(184, true));
	assert_ex(spell.couldBeString(185, true));
	
	
	assert_ex(spell.couldBeString(187));
	assert_ex(spell.couldBeString(188));
	assert_ex(spell.couldBeString(189, true));
	assert_ex(spell.couldBeString(190, true));
	assert_ex(spell.couldBeString(191, true));
	assert_ex(spell.couldBeString(192, true));
	assert_ex(spell.couldBeString(193, true));
	assert_ex(spell.couldBeString(194, true));
	assert_ex(spell.couldBeString(195, true));
	assert_ex(spell.couldBeString(196, true));
	assert_ex(spell.couldBeString(197, true));
	assert_ex(spell.couldBeString(198, true));
	assert_ex(spell.couldBeString(199, true));
	assert_ex(spell.couldBeString(200, true));
	assert_ex(spell.couldBeString(201, true));
	assert_ex(spell.couldBeString(202, true));
	
	
	//Cleanup
	
	for (auto file : files)
	{
		delete file;
	}
	return FKs;
}



void vtableTesting()
{
	
}






std::list<std::string> getFilenames()
{
	std::list<std::string> filenames;
	
	DIR* dirp = opendir("Test_Files/DBC");
	struct dirent* dp;
	while ((dp = readdir(dirp)) != NULL)
	{
		filenames.push_back(dp->d_name);
	}
	closedir(dirp);
	
	
	{
		auto it = filenames.begin();
		while (it != filenames.end())
		{
			if (QUtils::String(*it).toUpper().endsWith(".DBC"))
			{
				++it;
			}
			else
			{
				it = filenames.erase(it);
			}
		}
	}
	
	return filenames;
}