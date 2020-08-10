#ifndef CPR_CURL_HOLDER_H
#define CPR_CURL_HOLDER_H

#include <mutex>
#include <string>

#include <curl/curl.h>

namespace cpr {
struct CurlHolder {
  private:
    /**
     * Mutex for curl_easy_init().
     * curl_easy_init() is not thread save.
     * References:
     * https://curl.haxx.se/libcurl/c/curl_easy_init.html
     * https://curl.haxx.se/libcurl/c/threadsafe.html
     **/
    static std::mutex curl_easy_init_mutex_;

  public:
    CURL* handle{nullptr};
    struct curl_slist* chunk{nullptr};
    struct curl_httppost* formpost{nullptr};
    char error[CURL_ERROR_SIZE];

    CurlHolder();
    ~CurlHolder();

    /**
     * Uses curl_easy_escape(...) for escaping the given string.
     **/
    std::string urlEncode(const std::string& s) const;
};
} // namespace cpr

#endif
