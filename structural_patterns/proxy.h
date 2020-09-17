#ifndef PROXY_H
#define PROXY_H

#include <string>
#include <memory>
#include <iostream>

namespace Proxy
{

class HttpDownloader
{
public:
	HttpDownloader() = default;

	virtual void download(const std::string& url) = 0;
};

class RealHttpDownloader : public HttpDownloader
{
public:
	RealHttpDownloader() = default;

	void download(const std::string& url)
	{
		std::cout << "Download: " << url << std::endl;
	}
};


class ProxyHttpDownloader : public HttpDownloader
{
	std::unique_ptr<HttpDownloader> downloader;

	void authenticate(const std::string& url)
	{
		// apply the required authentication for this url
		std::cout << url << " authentication" << std::endl;
	}
public:
	ProxyHttpDownloader(HttpDownloader* downloader)
	{
		this->downloader = std::unique_ptr<HttpDownloader>(downloader);
	}

	void download(const std::string& url)
	{
		authenticate(url);
		this->downloader->download(url);
	}
};
} // namespace Proxy

#endif // PROXY_H
