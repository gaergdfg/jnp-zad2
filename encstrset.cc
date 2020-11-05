#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>


namespace {
	unsigned long global_id = 0;
	std::unordered_map <int, std::unordered_set <std::string>> encstrset;

	#ifdef NDEBUG
		static const bool debug = false;
	#else
		static const bool debug = true;
	#endif


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


	static void passDebugInfo(std::string info) {
		if (debug) {
			std::cerr << info;
		}
	}
}


unsigned long encstrset_new() {
	passDebugInfo("encstrset_new()\n");

	encstrset.insert(make_pair(global_id++, std::unordered_set<std::string>()));

	passDebugInfo(
		"encstrset_new: set #" +
		std::to_string(global_id) +
		" created\n"
	);

	return global_id - 1;
}


void encstrset_delete(unsigned long id) {
	passDebugInfo("encstrset_delete()\n");

	if (encstrset.count(id)) {
		encstrset.erase(id);
		passDebugInfo(
			"encstrset_delete: set#" +
			std::to_string(id) +
			" deleted\n"
		);
	}
	else {
		passDebugInfo(
			"encstrset_delete: set#" +
			std::to_string(id) +
			" does not exist\n"
		);
	}
}


size_t encstrset_size(unsigned long id) {
	passDebugInfo("encstrset_size(" + std::to_string(id) + ")\n");

	if (encstrset.count(id)) {
		passDebugInfo(
			"encstrset_size: set #" +
			std::to_string(id) +
			" contains " +
			std::to_string(encstrset[id].size()) +
			" element(s)\n"
		);
		return encstrset[id].size();
	}
	else {
		passDebugInfo(
			"encstrset_size: set#" +
			std::to_string(id) +
			" does not exist\n"
		);
	}
	return 0;
}


//TODO: cudzyslowia wokol stringow, ale nie wokol NULL'i
bool encstrset_insert(unsigned long id, const char *value, const char *key) {
	passDebugInfo(
		"encstrset_insert(" +
		std::to_string(id) +
		" " +
		(!(*value) ? "NULL" : value) +
		" " +
		(!(*key) ? "NULL" : key) +
		")\n"
	);

	if (!(*value)) {
		passDebugInfo("encstrset_insert: invalid value (NULL)\n");
		return false;
	}
	
	if (encstrset.count(id)) {
		std::string code;
		if (!(*key)) {
			code = std::string(value);
		}
		else {
			code = cypher(value, key);
		}

		if (encstrset[id].count(code)) {
			passDebugInfo(
				"encstrset_insert: set#" +
				std::to_string(id) +
				", cypher \"" +
				strToHex(code) +
				"\" was already present\n"
			);
		}
		else {
			encstrset[id].insert(code);
			passDebugInfo(
				"encstrset_insert: set#" +
				std::to_string(id) +
				", cypher \"" +
				strToHex(code) +
				"\" inserted\n"
			);
		}
		return true;
	}
	else {
		passDebugInfo(
			"encstrset_insert: set#" +
			std::to_string(id) +
			" does not exist\n"
		);
	}
	return false;
}


bool encstrset_remove(unsigned long id, const char* value, const char* key) {
	passDebugInfo(
		"encstrset_remove(" +
		std::to_string(id) +
		" " +
		(!(*value) ? "NULL" : value) +
		" " +
		(!(*key) ? "NULL" : key) +
		")\n"
	);

	if (!(*value)) {
		passDebugInfo("encstrset_remove: invalid value (NULL)\n");
		return false;
	}
	
	if (encstrset.count(id)) {
		std::string code;
		if (!(*key)) {
			code = std::string(value);
		}
		else {
			code = cypher(value, key);
		}

		if (encstrset[id].count(code)) {
			encstrset[id].erase(code);
			passDebugInfo(
				"encstrset_remove: set#" +
				std::to_string(id) +
				", cypher \"" +
				strToHex(code) +
				"\" removed\n"
			);
			return true;
		}
		else {
			passDebugInfo(
				"encstrset_remove: set#" +
				std::to_string(id) +
				", cypher \"" +
				strToHex(code) +
				"\" was not present\n"
			);
		}
	}
	else {
		passDebugInfo(
			"encstrset_remove: set#" +
			std::to_string(id) +
			" does not exist\n"
		);
	}
	return false;
}

bool encstrset_test(unsigned long id, const char* value, const char* key) {
	passDebugInfo(
		"encstrset_test(" +
		std::to_string(id) +
		" " +
		(!(*value) ? "NULL" : value) +
		" " +
		(!(*key) ? "NULL" : key) +
		")\n"
	);

	if (!(*value)) {
		passDebugInfo("encstrset_test: invalid value (NULL)\n");
		return false;
	}
	
	if (encstrset.count(id)) {
		std::string code;
		if (!(*key)) {
			code = std::string(value);
		}
		else {
			code = cypher(value, key);
		}
		
		if (encstrset[id].count(code)) {
			passDebugInfo(
				"encstrset_test: set#" +
				std::to_string(id) +
				", cypher \"" +
				strToHex(code) +
				"\" is present\n"
			);
			return true;
		}
		else {
			passDebugInfo(
				"encstrset_test: set#" +
				std::to_string(id) +
				", cypher \"" +
				strToHex(code) +
				"\" is not present\n"
			);
		}
	}
	else {
		passDebugInfo(
			"encstrset_test: set#" +
			std::to_string(id) +
			" does not exist\n"
		);
	}
	return false;
}


void encstrset_clear(unsigned long id) {
	passDebugInfo(
		"encstrset_clear(" +
		std::to_string(id) +
		")\n"
	);
	
	if (encstrset.count(id)) {
		encstrset[id].clear();
		passDebugInfo(
			"encstrset_clear: set#" +
			std::to_string(id) +
			" cleared\n"
		);
	}
	else {
		passDebugInfo(
			"encstrset_clear: set#" +
			std::to_string(id) +
			" does not exist\n"
		);
	}
}


void encstrset_copy(unsigned long src_id, unsigned long dst_id) {
	passDebugInfo(
		"encstrset_copy(" +
		std::to_string(src_id) +
		" " +
		std::to_string(dst_id) +
		")\n"
	);
	
	if (encstrset.count(src_id) && encstrset.count(dst_id)) {
		for (auto it : encstrset[src_id]) {
			if (encstrset[dst_id].count(it)) {
				passDebugInfo(
					"encstrset_copy: cypher \"" +
					strToHex(it) +
					"\" was already present in set #" +
					std::to_string(dst_id) +
					"\n"
				);
			}
			else {
				encstrset[dst_id].insert(it);
				passDebugInfo(
					"encstrset_copy: cypher \"" +
					strToHex(it) +
					"\" copied from set #" +
					std::to_string(src_id) +
					" to set #" +
					std::to_string(src_id) +
					"\n"
				);
			}
		}
	}
	else {
		if (!encstrset.count(src_id)) {
			passDebugInfo("encstrset_copy: set#" +
				std::to_string(src_id) +
				" does not exist\n"
			);
			return;
		}
		if (!encstrset.count(dst_id)) {
			passDebugInfo(
				"encstrset_copy: set#" +
				std::to_string(dst_id) +
				" does not exist\n"
			);
		}
	}
}
