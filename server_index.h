#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "server_tag.h"
#include "server_file.h"

/*Monitor del index que contien los tags y files con sus hashes*/
class Index {
 private:
  std::mutex m;
  const std::string config_filename;
  std::map<std::string, Tag> tags;
  std::map<std::string, File> files;

 public:
  explicit Index(const char* filename);
  virtual ~Index();

  /*Metodos para interactuar con el index*/
  /*file_add_hash_if_possible: si el archivo tiene el hash, retorna false;
      si no lo tiene, lo inserta y retorna true.*/
  bool file_add_hash_if_possible(std::string &filename, std::string &hash);
  /*get_files_with_tag: si el tag existe, retorna los hashes asociados;
      si no existe, retorna un vector vacio.*/
  std::vector<std::string> get_files_with_tag(std::string &tag);
  /*get_filename_of_hash: si encuentra el hash, retorna el nombre del archivo;
      si no lo encuentra, retorna un string vacio.*/
  std::string get_filename_of_hash(std::string &hash);
  /*add_tag_if_possible: si alguno de los hashes no existe, retorna false;
      si el tag existe, retorna false; si no existe, lo crea y retorna true.*/
  bool add_tag_if_possible(std::string &tag, std::vector<std::string> &hashes);
  
 private:
  /*Metodos auxiliares: no estan mutexados, usados por metodos mutexados*/
  bool tag_exists(std::string &tag);
  void add_file_hash(std::string &filename, std::string &hash);
  bool file_has_hash(std::string &filename, std::string &hash);
};

#endif
