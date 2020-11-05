#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>


namespace {
	unsigned long global_id = 0;
	std::unordered_map <int, std::unordered_set <std::string>> encstrset;

	
	static std::string cypher(const std::string &value, const std::string &key) {
		std::string result = "";
		for (int i = 0, j = 0; i < value.size(); i++, j = (j + 1) % key.size()) {
			result += value[i] ^ key[j];
		}
		return result;
	}


	static char chitos(char value) {
		return value > 9 ? ('A' + value - 10) : ('0' + value);

	}


	static std::string binToHex(char value) {
		char a = value >> 4;
		char b = value & 15;

		std::string result = "";
		result += chitos(a);
		result += chitos(b);

		return result;
	}


	static std::string strToHex(std::string &value) {
		std::string result = "";
		for (int i = 0; i < value.size(); i++) {
			result += binToHex(value[i]);
			if (i != value.size() - 1) {
				result += " ";
			}
		}
		return result;
	}
}


unsigned long encstrset_new() {
	encstrset.insert(make_pair(global_id++, std::unordered_set<std::string>()));
	return global_id - 1;
}


void encstrset_delete(unsigned long id) {
	encstrset.erase(id);
}


size_t encstrset_size(unsigned long id) {
	if (encstrset.count(id)) {
		return encstrset[id].size();
	}
	return 0;
}


bool encstrset_insert(unsigned long id, const char *value, const char *key) {
	if (encstrset.count(id)) {
		encstrset[id].insert(cypher(value, key));
		return true;
	}
	return false;
}


bool encstrset_remove(unsigned long id, const char* value, const char* key) {
	std::string code = cypher(value, key);
	if (encstrset.count(id) && encstrset[id].count(code)) {
		encstrset[id].erase(code);
		return true;
	}
	return false;
}

bool encstrset_test(unsigned long id, const char* value, const char* key) {
	std::string code = cypher(value, key);
	if (encstrset.count(id) && encstrset[id].count(code)) {
		return true;
	}
	return false;
}


void encstrset_clear(unsigned long id) {
	if (encstrset.count(id)) {
		encstrset[id].clear();
	}
}


void encstrset_copy(unsigned long src_id, unsigned long dst_id) {
	if (encstrset.count(src_id) && encstrset.count(dst_id)) {
		encstrset[dst_id] = std::unordered_set <std::string>(encstrset[src_id]);
	}
}
