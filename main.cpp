#include <bits/stdc++.h>
using namespace std;

/* ---------- Base62 Encoder ---------- */

class Base62Encoder {
    const string charset =
        "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

public:
    string encode(long long value) {
        if (value == 0) return "0";

        string result;
        while (value > 0) {
            result.push_back(charset[value % 62]);
            value /= 62;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

/* ---------- Storage Layer ---------- */

struct URLRecord {
    string originalUrl;
    time_t expiryTime;
};

class URLStorage {
    unordered_map<string, URLRecord> storage;

public:
    void save(const string& shortKey, const string& url, int ttl) {
        time_t currentTime = time(nullptr);
        storage[shortKey] = {url, currentTime + ttl};
    }

    bool exists(const string& shortKey) const {
        return storage.find(shortKey) != storage.end();
    }

    string fetch(const string& shortKey) {
        auto it = storage.find(shortKey);
        if (it == storage.end()) return "";

        time_t currentTime = time(nullptr);
        if (currentTime > it->second.expiryTime) {
            storage.erase(it);
            return "";
        }
        return it->second.originalUrl;
    }
};

/* ---------- Service Layer ---------- */

class URLShortenerService {
    Base62Encoder encoder;
    URLStorage storage;
    long long counter;

    string generateKey(const string& url) {
        long long hashValue = hash<string>{}(url);
        return encoder.encode(llabs(hashValue));
    }

public:
    URLShortenerService() : counter(100000) {}

    string shorten(const string& longUrl, int ttl = 3600,
                   const string& customAlias = "") {
        string key;

        if (!customAlias.empty()) {
            if (storage.exists(customAlias))
                return "Alias already exists";
            key = customAlias;
        } else {
            key = generateKey(longUrl);
            while (storage.exists(key)) {
                key = encoder.encode(counter++);
            }
        }

        storage.save(key, longUrl, ttl);
        return key;
    }

    string expand(const string& shortKey) {
        return storage.fetch(shortKey);
    }
};

/* ---------- Driver Code ---------- */

int main() {
    URLShortenerService service;

    string shortUrl1 = service.shorten(
        "https://www.google.com/careers", 10);
    cout << "Short URL: " << shortUrl1 << endl;

    string shortUrl2 = service.shorten(
        "https://openai.com/research", 20, "openAI");
    cout << "Custom Short URL: " << shortUrl2 << endl;

    cout << "Expanded: " << service.expand(shortUrl1) << endl;
    cout << "Expanded: " << service.expand("openAI") << endl;

    return 0;
}
