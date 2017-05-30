#include "XmlDocument.h"
//
////---------------------------------------------------------------
//// Name: TryGetValueAs
//// Desc: returns false if 
////---------------------------------------------------------------
//bool XmlTag::TryGetValueAs(const string& name, float* value)
//{
//	if (this->NameExists(name)) {
//		try {
//			*value = stof(this->nameValuePairs[name]);
//		}
//		catch (invalid_argument e) {
//			return false;
//		}
//		catch (out_of_range e) {
//			return false;
//		}
//	}
//
//	return false;
//}
////---------------------------------------------------------------
//// Name: TryGetValueAs
//// Desc: returns false if 
////---------------------------------------------------------------
//bool XmlTag::TryGetValueAs(const string& name, int* value)
//{
//	if (this->NameExists(name)) {
//		try {
//			*value = stoi(this->nameValuePairs[name]);
//		}
//		catch (invalid_argument e) {
//			return false;
//		}
//		catch (out_of_range e) {
//			return false;
//		}
//
//		return true;
//	}
//
//	return false;
//}
////---------------------------------------------------------------
//// Name: TryGetValueAs
//// Desc: returns false if 
////---------------------------------------------------------------
//bool XmlTag::TryGetValueAs(const string& name, string* value)
//{
//	if (this->NameExists(name)) {
//		*value = this->nameValuePairs[name];
//		return true;
//	}
//
//	return false;
//}
