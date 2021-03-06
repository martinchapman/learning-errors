/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class de_libalf_jni_JNIKnowledgebase */

#ifndef _Included_de_libalf_jni_JNIKnowledgebase
#define _Included_de_libalf_jni_JNIKnowledgebase
#ifdef __cplusplus
extern "C" {
#endif
#undef de_libalf_jni_JNIKnowledgebase_serialVersionUID
#define de_libalf_jni_JNIKnowledgebase_serialVersionUID 2LL
#undef de_libalf_jni_JNIKnowledgebase_ACCEPTANCE_TRUE
#define de_libalf_jni_JNIKnowledgebase_ACCEPTANCE_TRUE 2L
#undef de_libalf_jni_JNIKnowledgebase_ACCEPTANCE_FALSE
#define de_libalf_jni_JNIKnowledgebase_ACCEPTANCE_FALSE 0L
#undef de_libalf_jni_JNIKnowledgebase_ACCEPTANCE_UNKNOWN
#define de_libalf_jni_JNIKnowledgebase_ACCEPTANCE_UNKNOWN 1L
/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    init
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_de_libalf_jni_JNIKnowledgebase_init
  (JNIEnv *, jobject);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    is_answered
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_libalf_jni_JNIKnowledgebase_is_1answered
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    get_knowledge
 * Signature: (J)Ljava/util/LinkedList;
 */
JNIEXPORT jobject JNICALL Java_de_libalf_jni_JNIKnowledgebase_get_1knowledge
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    is_empty
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_libalf_jni_JNIKnowledgebase_is_1empty
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    count_queries
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_libalf_jni_JNIKnowledgebase_count_1queries
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    get_queries
 * Signature: (J)Ljava/util/LinkedList;
 */
JNIEXPORT jobject JNICALL Java_de_libalf_jni_JNIKnowledgebase_get_1queries
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    resolve_query
 * Signature: ([IJ)I
 */
JNIEXPORT jint JNICALL Java_de_libalf_jni_JNIKnowledgebase_resolve_1query
  (JNIEnv *, jobject, jintArray, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    resolve_or_add_query
 * Signature: ([IJ)I
 */
JNIEXPORT jint JNICALL Java_de_libalf_jni_JNIKnowledgebase_resolve_1or_1add_1query
  (JNIEnv *, jobject, jintArray, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    add_knowledge
 * Signature: ([IZJ)Z
 */
JNIEXPORT jboolean JNICALL Java_de_libalf_jni_JNIKnowledgebase_add_1knowledge
  (JNIEnv *, jobject, jintArray, jboolean, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    clear
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_libalf_jni_JNIKnowledgebase_clear
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    clear_queries
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_libalf_jni_JNIKnowledgebase_clear_1queries
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    undo
 * Signature: (IJ)Z
 */
JNIEXPORT jboolean JNICALL Java_de_libalf_jni_JNIKnowledgebase_undo
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    get_memory_usage
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_libalf_jni_JNIKnowledgebase_get_1memory_1usage
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    count_answers
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_libalf_jni_JNIKnowledgebase_count_1answers
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    generate_dotfile
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_de_libalf_jni_JNIKnowledgebase_generate_1dotfile
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    serialize
 * Signature: (J)[I
 */
JNIEXPORT jintArray JNICALL Java_de_libalf_jni_JNIKnowledgebase_serialize
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_libalf_jni_JNIKnowledgebase_destroy
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    deserialize
 * Signature: ([IJ)Z
 */
JNIEXPORT jboolean JNICALL Java_de_libalf_jni_JNIKnowledgebase_deserialize
  (JNIEnv *, jobject, jintArray, jlong);

/*
 * Class:     de_libalf_jni_JNIKnowledgebase
 * Method:    tostring
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_de_libalf_jni_JNIKnowledgebase_tostring
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
