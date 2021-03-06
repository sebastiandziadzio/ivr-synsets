#include <Python.h>
#include <string>
#include <vector>

#include "wordnet_reader.h"

Wordnet::Reader::Reader() {
}

bool Wordnet::Reader::isKnown(std::string word) {
  PyObject* moduleName = PyUnicode_FromString(Wordnet::MODULE_NAME);
  PyObject* moduleObject = PyImport_Import(moduleName);
  Py_DECREF(moduleName);

  PyObject* args = Py_BuildValue("(s)", word.c_str());
  PyObject*  isKnown = PyObject_GetAttrString(moduleObject, "is_known");
  Py_DECREF(moduleObject);

  PyObject* resultObj = PyObject_CallObject(isKnown, args);
  Py_DECREF(isKnown);
  Py_DECREF(args);

  const int result = PyObject_IsTrue(resultObj);
  return (bool)result;
}

bool Wordnet::Reader::areSynonyms(std::string word, std::string otherWord) {
  PyObject* moduleName = PyUnicode_FromString(Wordnet::MODULE_NAME);
  PyObject* moduleObject = PyImport_Import(moduleName);
  Py_DECREF(moduleName);

  PyObject* args = Py_BuildValue("ss", word.c_str(), otherWord.c_str());
  PyObject*  areSynonyms = PyObject_GetAttrString(moduleObject, "are_synonyms");
  Py_DECREF(moduleObject);

  PyObject* resultObj = PyObject_CallObject(areSynonyms, args);
  Py_DECREF(areSynonyms);
  Py_DECREF(args);

  const int result = PyObject_IsTrue(resultObj);
  return (bool)result;
}

std::vector<std::string> Wordnet::Reader::getSynonymsOf(std::string word) {
  PyObject* moduleName = PyUnicode_FromString(Wordnet::MODULE_NAME);
  PyObject* moduleObject = PyImport_Import(moduleName);
  Py_DECREF(moduleName);

  PyObject* args = Py_BuildValue("(s)", word.c_str());
  PyObject*  getSynonymsOf = PyObject_GetAttrString(moduleObject, "get_synonyms");
  Py_DECREF(moduleObject);

  PyObject* resultObj = PyObject_CallObject(getSynonymsOf, args);
  Py_DECREF(getSynonymsOf);
  Py_DECREF(args);

  Py_ssize_t i, n;
  PyObject* listItem;
  std::vector<std::string> synonyms;

  n = PyList_Size(resultObj);
  for (i = 0; i < n; i++) {
      listItem = PyList_GetItem(resultObj, i);
      PyObject* pyStr = PyUnicode_AsEncodedString(listItem, "utf-8", "Error ~");
      Py_DECREF(listItem);
      synonyms.push_back(PyBytes_AS_STRING(pyStr));
  }
  return synonyms;
}

std::vector<std::string> Wordnet::Reader::getHyponymsOf(std::string word, int level) {
  PyObject* moduleName = PyUnicode_FromString(Wordnet::MODULE_NAME);
  PyObject* moduleObject = PyImport_Import(moduleName);
  Py_DECREF(moduleName);

  PyObject* args = Py_BuildValue("(si)", word.c_str(), level);
  PyObject* getHyponymsOf = PyObject_GetAttrString(moduleObject, "get_hyponyms");
  Py_DECREF(moduleObject);

  PyObject* resultObj = PyObject_CallObject(getHyponymsOf, args);
  Py_DECREF(getHyponymsOf);
  Py_DECREF(args);

  Py_ssize_t i, n;
  PyObject* listItem;
  std::vector<std::string> hyponyms;

  n = PyList_Size(resultObj);
  for (i = 0; i < n; i++) {
      listItem = PyList_GetItem(resultObj, i);
      PyObject* pyStr = PyUnicode_AsEncodedString(listItem, "utf-8", "Error ~");
      Py_DECREF(listItem);
      hyponyms.push_back(PyBytes_AS_STRING(pyStr));
  }
  return hyponyms;
}

