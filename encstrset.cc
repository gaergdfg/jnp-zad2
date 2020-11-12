#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include "encstrset.h"


using map_of_sets =
	std::unordered_map <unsigned long, std::unordered_set <std::string>>;


namespace jnp1 {
	namespace {
		
		/* Tworzy nowa instancje globalnej zmiennej global_id, jesli nie istnieje.
		Zwraca globalna zmienna global_id. */
		unsigned long long &global_id() {
			static unsigned long long *res = new unsigned long long();
			return *res;
		}


		/* Tworzy nowa instancje globalnej zmiennej encstrset, jesli nie istnieje.
		Zwraca globalna zmienna encstrset. */
		map_of_sets &encstrset() {
			static map_of_sets *res = new map_of_sets();
			return *res;
		}
		
		
		#ifdef NDEBUG
			static const bool debug = false;
		#else
			static const bool debug = true;
		#endif


		/* Szyfruje (deszyfruje) dane zawarte w value za pomoca klucza key metoda xorowania bitow.
		Zwraca zaszyfrowana (odszyfrowana) wiadomosc. */
		std::string cypher(const std::string &value, const std::string &key) {
			if (key.empty()) {
				return std::string(value);
			}

			std::string result = "";
			for (unsigned int i = 0, j = 0; i < value.size(); i++, j = (j + 1) % key.size()) {
				result += value[i] ^ key[j];
			}
			return result;
		}


		/* Zamienia wartosc value na odpowiadajacy mu znak w systemie szesnastkowym. */
		char numToHex(char value) {
			return value > 9 ? ('A' + value - 10) : ('0' + value);
		}


		/* Konwertuje pojedynczy znak na jego wartosc szestnastkowa i go zwraca. */
		std::string binToHex(char value) {
			char a = (unsigned char)value >> 4; /* Wartoœæ utorzona z 4 najbardziej znacz¹cych bitów */
			char b = (unsigned char)value & 15; /* Wartoœæ utorzona z 4 najmniej znacz¹cych bitów */

			std::string result = "";
			result += numToHex(a);
			result += numToHex(b);

			return result;
		}


		/* Konwertuje, znak po znaku, string na jego szestanstkowy odpowiednik i go zwraca. */
		std::string strToHex(std::string &value) {
			std::string result = "";
			for (unsigned int i = 0; i < value.size(); i++) {
				result += binToHex(value[i]);
				if (i != value.size() - 1) {
					result += " ";
				}
			}
			return result;
		}


		/* Wypisuje na wyjscie diagnostyczne infomracje zawarte w info. */
		void passDebugInfo(std::string &info) {
			if (debug) {
				std::cerr << info;
			}
		}


		/* Konwertuje podane przez uzytkownika dane na 
		stringa z odpowiednimi informacjami diagnostycznymi.
		Jezeli podany argument nie jest nullem, to otacza go cudzyslowiem. */
		std::string inputToString(
			std::string& functionName,
			unsigned long id,
			const char* value,
			const char* key
		) {
			std::string result = functionName + "(" + std::to_string(id) + ", ";

			if (value == NULL)
				result += "NULL";
			else {
				std::string s1(value);
				result += ("\"" + s1 + "\"");
			}
			result += ", ";

			if (key == NULL)
				result += "NULL";
			else {
				std::string s2(key);
				result += ("\"" + s2 + "\"");
			}
			result +=")\n";
			
			return result;
		}
	}


	unsigned long encstrset_new() {
		std::string debugMessage = "encstrset_new()\n";
		passDebugInfo(debugMessage);

		encstrset().insert(
			make_pair(global_id(), std::unordered_set<std::string>())
		);

		debugMessage =
			"encstrset_new: set #" +
			std::to_string(global_id()) +
			" created\n";
		passDebugInfo(debugMessage);

		return global_id()++;
	}


	void encstrset_delete(unsigned long id) {
		std::string debugMessage = "encstrset_delete(" + std::to_string(id) + ")\n";
		passDebugInfo(debugMessage);

		if (encstrset().count(id)) {
			encstrset().erase(id);
			debugMessage = 
				"encstrset_delete: set #" +
				std::to_string(id) +
				" deleted\n";
			passDebugInfo(debugMessage);
		}
		else {
			debugMessage =
				"encstrset_delete: set #" +
				std::to_string(id) +
				" does not exist\n";
			passDebugInfo(debugMessage);
		}
	}


	size_t encstrset_size(unsigned long id) {
		std::string debugMessage = "encstrset_size(" + std::to_string(id) + ")\n";
		passDebugInfo(debugMessage);

		if (encstrset().count(id)) {
			size_t res = encstrset()[id].size();
			debugMessage =
				"encstrset_size: set #" +
				std::to_string(id) +
				" contains " +
				std::to_string(encstrset()[id].size()) +
				" element(s)\n";
			passDebugInfo(debugMessage);
			return res;
		}
		else {
			debugMessage =
				"encstrset_size: set #" +
				std::to_string(id) +
				" does not exist\n";
			passDebugInfo(debugMessage);
		}

		return 0;
	}


	bool encstrset_insert(unsigned long id, const char *value, const char *key) {
		std::string functionName = "encstrset_insert";
		std::string debugMessage = inputToString(functionName, id, value, key);
		passDebugInfo(debugMessage);

		if (value == NULL) {
			debugMessage = "encstrset_insert: invalid value (NULL)\n";
			passDebugInfo(debugMessage);
			return false;
		}
		
		if (encstrset().count(id)) {
			std::string code;
			if (key == NULL) {
				code = std::string(value);
			}
			else {
				code = cypher(value, key);
			}

			if (encstrset()[id].count(code)) {
				debugMessage = 
					"encstrset_insert: set #" +
					std::to_string(id) +
					", cypher \"" +
					strToHex(code) +
					"\" was already present\n";
				passDebugInfo(debugMessage);
				return false;
			}
			else {
				encstrset()[id].insert(code);
				debugMessage = 
					"encstrset_insert: set #" +
					std::to_string(id) +
					", cypher \"" +
					strToHex(code) +
					"\" inserted\n";
				passDebugInfo(debugMessage);
				return true;
			}
		}
		else {
			debugMessage =
				"encstrset_insert: set #" +
				std::to_string(id) +
				" does not exist\n";
			passDebugInfo(debugMessage);
		}
		return false;
	}


	bool encstrset_remove(unsigned long id, const char* value, const char* key) {
		std::string functionName = "encstrset_remove";
		std::string debugMessage = inputToString(functionName, id, value, key);
		passDebugInfo(debugMessage);

		if (value == NULL) {
			debugMessage = "encstrset_remove: invalid value (NULL)\n";
			passDebugInfo(debugMessage);
			return false;
		}
		
		if (encstrset().count(id)) {
			std::string code;
			if (key == NULL) {
				code = std::string(value);
			}
			else {
				code = cypher(value, key);
			}

			if (encstrset()[id].count(code)) {
				encstrset()[id].erase(code);
				debugMessage =
					"encstrset_remove: set #" +
					std::to_string(id) +
					", cypher \"" +
					strToHex(code) +
					"\" removed\n";
				passDebugInfo(debugMessage);
				return true;
			}
			else {
				debugMessage =
					"encstrset_remove: set #" +
					std::to_string(id) +
					", cypher \"" +
					strToHex(code) +
					"\" was not present\n";
				passDebugInfo(debugMessage);
			}
		}
		else {
			debugMessage =
				"encstrset_remove: set #" +
				std::to_string(id) +
				" does not exist\n";
			passDebugInfo(debugMessage);
		}
		return false;
	}

	bool encstrset_test(unsigned long id, const char* value, const char* key) {
		std::string functionName = "encstrset_test";
		std::string debugMessage = inputToString(functionName, id, value, key);
		passDebugInfo(debugMessage);

		if (value == NULL) {
			debugMessage = "encstrset_test: invalid value (NULL)\n";
			passDebugInfo(debugMessage);
			return false;
		}
		
		if (encstrset().count(id)) {
			std::string code;
			if (key == NULL) {
				code = std::string(value);
			}
			else {
				code = cypher(value, key);
			}
			
			if (encstrset()[id].count(code)) {
				debugMessage =
					"encstrset_test: set #" +
					std::to_string(id) +
					", cypher \"" +
					strToHex(code) +
					"\" is present\n";
				passDebugInfo(debugMessage);
				return true;
			}
			else {
				debugMessage =
					"encstrset_test: set #" +
					std::to_string(id) +
					", cypher \"" +
					strToHex(code) +
					"\" is not present\n";
				passDebugInfo(debugMessage);
			}
		}
		else {
			debugMessage = 
				"encstrset_test: set #" +
				std::to_string(id) +
				" does not exist\n";
			passDebugInfo(debugMessage);
		}
		return false;
	}


	void encstrset_clear(unsigned long id) {
		std::string debugMessage =
			"encstrset_clear(" +
			std::to_string(id) +
			")\n";
		passDebugInfo(debugMessage);
		
		if (encstrset().count(id)) {
			encstrset()[id].clear();
			debugMessage =
				"encstrset_clear: set #" +
				std::to_string(id) +
				" cleared\n";
			passDebugInfo(debugMessage);
		}
		else {
			debugMessage = 
				"encstrset_clear: set #" +
				std::to_string(id) +
				" does not exist\n";
			passDebugInfo(debugMessage);
		}
	}


	void encstrset_copy(unsigned long src_id, unsigned long dst_id) {
		std::string debugMessage = 
			"encstrset_copy(" +
			std::to_string(src_id) +
			", " +
			std::to_string(dst_id) +
			")\n";
		passDebugInfo(debugMessage);
		
		if (encstrset().count(src_id) && encstrset().count(dst_id)) {
			for (auto it : encstrset()[src_id]) {
				if (encstrset()[dst_id].count(it)) {
					debugMessage =
						"encstrset_copy: copied cypher \"" +
						strToHex(it) +
						"\" was already present in set #" +
						std::to_string(dst_id) +
						"\n";
					passDebugInfo(debugMessage);
				}
				else {
					encstrset()[dst_id].insert(it);
					debugMessage = 
						"encstrset_copy: cypher \"" +
						strToHex(it) +
						"\" copied from set #" +
						std::to_string(src_id) +
						" to set #" +
						std::to_string(dst_id) +
						"\n";
					passDebugInfo(debugMessage);
				}
			}
		}
		else {
			if (!encstrset().count(src_id)) {
				 debugMessage = 
					 "encstrset_copy: set #" +
					std::to_string(src_id) +
					" does not exist\n";
					passDebugInfo(debugMessage);
				return;
			}
			if (!encstrset().count(dst_id)) {
				debugMessage = "encstrset_copy: set #" +
					std::to_string(dst_id) +
					" does not exist\n";
				passDebugInfo(debugMessage);
			}
		}
	}
}
