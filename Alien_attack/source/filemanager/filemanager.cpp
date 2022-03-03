/// @file filemanager.cpp
/// @brief Implementing of the file management system.
#include <filemanager/filemanager.hpp>

#include <algorithm>


namespace Engine {

Filemanager* Filemanager::m_instance{ nullptr };


Filemanager* Filemanager::Instance() {
	if(!m_instance) {
		m_instance = new Filemanager();
	}
	return m_instance;
}


std::optional<std::string> Filemanager::FindFile(const std::string& filename) const {
	return FindFile(filename, m_contentDir);
}


std::optional<std::string> Filemanager::FindFile(const std::string& filename,
												 const filesystem::path& initialPath) const {
	auto clearedFilename{ MakePreferredSeparator(RemoveSpecialCharacters(filename)) };
	auto pathFile{ filesystem::path(clearedFilename) };
	for(const auto& file : filesystem::recursive_directory_iterator{ initialPath }) {
		auto filePath{ MakePreferredSeparator(file.path().string()) };
		auto position{ filePath.find(pathFile.string()) };
		if(std::string::npos != position) {
			if(0 == position || '/' == filePath[--position] ) {
				return file.path().string();
			}
		}
	}

	return std::nullopt;
}


std::optional<std::string> Filemanager::FindAsset(const std::string& filename) const {
	auto pathFile{ FindFile(filename, m_assetsDir) };
	return (pathFile) ? pathFile : FindFile(filename, m_contentDir);
}


std::optional<std::string> Filemanager::FindMapContent(const std::string& filename) const {
	auto pathFile{ FindFile(filename, m_mapsDir) };
	return (pathFile) ? pathFile : FindFile(filename, m_contentDir);
}


std::optional<std::string> Filemanager::FindObjectDescription(const std::string& filename) const {
	auto pathFile{ FindFile(filename, m_objectDescriptionDir) };
	return (pathFile) ? pathFile : FindFile(filename, m_contentDir);
}


void Filemanager::SetPathToContent(const std::string& path) {
	m_contentDir = path;
}


std::string Filemanager::GetPathToContent() const {
	return m_contentDir.string();
}


std::string Filemanager::GetPathToAssets() const {
	return m_assetsDir.string();
}


std::string Filemanager::GetPathToMaps() const {
	return m_mapsDir.string();
}


std::string Filemanager::GetPathToObjectDescription() const {
	return m_objectDescriptionDir.string();
}


std::string Filemanager::RemoveSpecialCharacters(const std::string& path) const {
	const std::vector<std::string> specSymbols{
		"../", "./", "/"
	};
	auto str{ path };
	for(const auto& symbol : specSymbols) {
		if(str.find(symbol) == 0) {
			str.erase(0, symbol.length());
			break;
		}
	}
	return str;
}


std::string Filemanager::MakePreferredSeparator(const std::string& path) const {
	auto str{ path };
	std::replace_if(str.begin(), str.end(),
		[](char c) { return (c == '\\'); }, '/');
	return str;
}


void Filemanager::SetAssetsDir() {
	auto assetsDir{ FindFile("assets")};
	if(assetsDir) {
		m_assetsDir = assetsDir.value();
	}
}


void Filemanager::SetMapsDir() {
	auto mapsDir{ FindFile("maps")};
	if(mapsDir) {
		m_mapsDir = mapsDir.value();
	}
}


void Filemanager::SetObjectDescriptionDir() {
	auto objectDescription{ FindFile("xml")};
	if(objectDescription) {
		m_objectDescriptionDir = objectDescription.value();
	}
}

} // namespace Engine
