/// @file filemanager.hpp
/// @brief Description of the file management system.
#pragma once

#ifndef __FILEMANAGER_HPP__
#define __FILEMANAGER_HPP__

#include <optional>

#ifdef GCC_EXPERIMENTAL
#include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;
#else
#include <filesystem>
namespace filesystem = std::filesystem;
#endif


namespace Engine {

constexpr auto GAME_STATES_FILE{ "states.xml" };
constexpr auto GAME_STORIES_FILE{ "stories.xml" };


namespace { // anonymous namespace

const filesystem::path DEFAULT_CONTENT_DIR{ "../content/" };
const filesystem::path DEFAULT_ASSETS_DIR{ DEFAULT_CONTENT_DIR.string() + std::string{ "assets/" } };
const filesystem::path DEFAULT_MAPS_DIR{ DEFAULT_CONTENT_DIR.string() + std::string{ "maps/" } };
const filesystem::path DEFAULT_OBJECT_DESCRIPTRION_DIR{ DEFAULT_CONTENT_DIR.string() + std::string{ "xml/" } };

} // namespace anonymous


/// @brief File management system.
class Filemanager {
public:
	~Filemanager() = default;

	static Filemanager* Instance();

	std::optional<std::string> FindFile(const std::string& filename) const;
	std::optional<std::string> FindFile(const std::string& filename,
										const filesystem::path& initialPath) const;
	std::optional<std::string> FindAsset(const std::string& filename) const;
	std::optional<std::string> FindMapContent(const std::string& filename) const;
	std::optional<std::string> FindObjectDescription(const std::string& filename) const;

	void SetPathToContent(const std::string& path);

	std::string GetPathToContent() const;
	std::string GetPathToAssets() const;
	std::string GetPathToMaps() const;
	std::string GetPathToObjectDescription() const;

private:
	Filemanager() = default;

	/// @brief Remove special characters from the path.
	/// @note Special characters at the beginning of a line, such as:
	///			"/", "./", "../".
	std::string RemoveSpecialCharacters(const std::string& path) const;

	/// @brief Replace the separators with the system's preferred separators.
	std::string MakePreferredSeparator(const std::string& path) const;

	void SetAssetsDir();
	void SetMapsDir();
	void SetObjectDescriptionDir();

private:
	static Filemanager* m_instance;

	filesystem::path m_contentDir{ DEFAULT_CONTENT_DIR };
	filesystem::path m_assetsDir{ DEFAULT_ASSETS_DIR };
	filesystem::path m_mapsDir{ DEFAULT_MAPS_DIR };
	filesystem::path m_objectDescriptionDir{ DEFAULT_OBJECT_DESCRIPTRION_DIR };
};

} // namespace Engine


#endif // !defined(__FILEMANAGER_HPP__)
