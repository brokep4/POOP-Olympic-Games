#include "projekat_SysClass.h"
#include <string>
#include "System.h"
#include <iostream>
#include <stdio.h>

using namespace std;

string jstring2string(JNIEnv* env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray)env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t)env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    string ret = string((char*)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

JNIEXPORT jlong JNICALL Java_projekat_SysClass_generateFilter
(JNIEnv* _env, jclass, jlong pointer, jstring _sportName, jobject _year, jstring _type, jstring _medal)
{
    jclass integer_class = _env->FindClass("java/lang/Integer");
    int year = _env->CallIntMethod(_year, _env->GetMethodID(integer_class, "intValue", "()I"));
    string sportName = jstring2string(_env, _sportName);
    string type = jstring2string(_env, _type);
    string medal = jstring2string(_env, _medal);
    System* sys = (System*)pointer;
    Medal* med = nullptr;
    CompetitionType* compt = nullptr;
    if (type == "Team")compt = new CompetitionType(CompetitionType::Team);
    if (type == "Individual")compt = new CompetitionType(CompetitionType::Individual);
    if (medal == "Gold")med = new Medal(Medal::Gold);
    if (medal == "Silver")med = new Medal(Medal::Silver);
    if (medal == "Bronze")med = new Medal(Medal::Bronze);
    if (medal == "None")med = new Medal(Medal::None);
    return (jlong)sys->generateFilter(sportName, "", year, compt, med);
}

JNIEXPORT jobject JNICALL Java_projekat_SysClass__1numberOfParticipantsGroupedByCountry
(JNIEnv* _env, jclass _class, jlong _pointer, jlong _filterPointer)
{
    System* sys = (System*)_pointer;
    Filter* filter = (Filter*)_filterPointer;
    map<string, int> mapa = sys->numberOfParticipants2(filter);
    jclass mapClass = _env->FindClass("java/util/HashMap");
    jsize map_len = 1;
    jmethodID init = _env->GetMethodID(mapClass, "<init>", "(I)V");
    jobject hashMap = _env->NewObject(mapClass, init, map_len);
    jmethodID put = _env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    
    /*
    jclass cls = (*env)->FindClass(env, "java/lang/Integer");
    jmethodID midInit = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
    if (NULL == midInit) return NULL;
    jobject newObj = (*env)->NewObject(env, cls, midInit, number);
    */

    jclass cls = _env->FindClass("java/lang/Integer");
    jmethodID midInit = _env->GetMethodID(cls, "<init>", "(I)V");
    for (auto par : mapa)
    {
        jobject newObj = _env->NewObject(cls, midInit, par.second); // Integer
        _env->CallObjectMethod(hashMap, put, _env->NewStringUTF(par.first.c_str()), newObj);
    }
    return hashMap;

    //_env->CallObjectMethod(hashMap, put, _env->NewStringUTF("URL_TEST_API"), _env->NewStringUTF("home.php"));

}

JNIEXPORT jlong JNICALL Java_projekat_SysClass__1createObject
(JNIEnv*, jclass)
{
    printf("In C++ object creation!\n");
    return (jlong)(new System());
}

JNIEXPORT void JNICALL Java_projekat_SysClass__1deleteObject
(JNIEnv* _env, jclass, jlong pointer)
{
    System* sys = (System*)pointer;
    delete sys;
}

JNIEXPORT jboolean JNICALL Java_projekat_SysClass__1loadGroupMode
(JNIEnv* _env, jclass, jlong _pointer, jstring _path)
{
    string path = jstring2string(_env, _path);
    System* sys = (System*)_pointer;
    return (jboolean)sys->loadGroupMode(path);
}

JNIEXPORT jboolean JNICALL Java_projekat_SysClass__1loadIndividualMode
(JNIEnv* _env, jclass, jlong _pointer, jstring _path, jint _year)
{
    string path = jstring2string(_env, _path);
    System* sys = (System*)_pointer;
    return (jboolean)sys->loadIndividualMode(path, (int)_year);
}

JNIEXPORT jboolean JNICALL Java_projekat_SysClass__1loadAthletes
(JNIEnv* _env, jclass, jlong _pointer, jstring _path)
{
    cout << "I am here!\n";
    string path = jstring2string(_env, _path);
    System* sys = (System*)_pointer;
    return (jboolean)sys->loadAthletes(path);
}

JNIEXPORT jobject JNICALL Java_projekat_SysClass__1numberOfDisciplinesGroupedByOlGames
(JNIEnv* _env, jclass, jlong _pointer, jlong _filterPointer)
{
    System* sys = (System*)_pointer;
    Filter* filter = (Filter*)_filterPointer;
    map<string, int> mapa = sys->numberOfDisciplines2(filter);
    jclass mapClass = _env->FindClass("java/util/HashMap");
    jsize map_len = 1;
    jmethodID init = _env->GetMethodID(mapClass, "<init>", "(I)V");
    jobject hashMap = _env->NewObject(mapClass, init, map_len);
    jmethodID put = _env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    /*
    jclass cls = (*env)->FindClass(env, "java/lang/Integer");
    jmethodID midInit = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
    if (NULL == midInit) return NULL;
    jobject newObj = (*env)->NewObject(env, cls, midInit, number);
    */

    jclass cls = _env->FindClass("java/lang/Integer");
    jmethodID midInit = _env->GetMethodID(cls, "<init>", "(I)V");
    for (auto par : mapa)
    {
        jobject newObj = _env->NewObject(cls, midInit, par.second); // Integer
        _env->CallObjectMethod(hashMap, put, _env->NewStringUTF(par.first.c_str()), newObj);
    }
    return hashMap;
}

JNIEXPORT jobject JNICALL Java_projekat_SysClass__1averageHeightGroupedByOlGames
(JNIEnv* _env, jclass, jlong _pointer, jlong _filterPointer)
{
    System* sys = (System*)_pointer;
    Filter* filter = (Filter*)_filterPointer;
    map<string, double> mapa = sys->averageHeight2(filter);
    jclass mapClass = _env->FindClass("java/util/HashMap");
    jsize map_len = 1;
    jmethodID init = _env->GetMethodID(mapClass, "<init>", "(I)V");
    jobject hashMap = _env->NewObject(mapClass, init, map_len);
    jmethodID put = _env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    /*
    jclass cls = (*env)->FindClass(env, "java/lang/Integer");
    jmethodID midInit = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
    if (NULL == midInit) return NULL;
    jobject newObj = (*env)->NewObject(env, cls, midInit, number);
    */

    jclass cls = _env->FindClass("java/lang/Double"); //jclass cls = _env->FindClass("java/lang/Double");
    jmethodID midInit = _env->GetMethodID(cls, "<init>", "(D)V");
    for (auto par : mapa)
    {
        //continue;
        jobject newObj = _env->NewObject(cls, midInit, (jdouble)par.second); // Double
        _env->CallObjectMethod(hashMap, put, _env->NewStringUTF(par.first.c_str()), newObj);
    }
    return hashMap;
}

JNIEXPORT jobject JNICALL Java_projekat_SysClass__1averageWeightGroupedByOlGames
(JNIEnv* _env, jclass, jlong _pointer, jlong _filterPointer)
{
    System* sys = (System*)_pointer;
    Filter* filter = (Filter*)_filterPointer;
    map<string, double> mapa = sys->averageWeight2(filter);
    jclass mapClass = _env->FindClass("java/util/HashMap");
    jsize map_len = 1;
    jmethodID init = _env->GetMethodID(mapClass, "<init>", "(I)V");
    jobject hashMap = _env->NewObject(mapClass, init, map_len);
    jmethodID put = _env->GetMethodID(mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    /*
    jclass cls = (*env)->FindClass(env, "java/lang/Integer");
    jmethodID midInit = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
    if (NULL == midInit) return NULL;
    jobject newObj = (*env)->NewObject(env, cls, midInit, number);
    */

    jclass cls = _env->FindClass("java/lang/Double"); //jclass cls = _env->FindClass("java/lang/Double");
    jmethodID midInit = _env->GetMethodID(cls, "<init>", "(D)V");
    for (auto par : mapa)
    {
        //continue;
        jobject newObj = _env->NewObject(cls, midInit, (jdouble)par.second); // Double
        _env->CallObjectMethod(hashMap, put, _env->NewStringUTF(par.first.c_str()), newObj);
    }
    return hashMap;
}