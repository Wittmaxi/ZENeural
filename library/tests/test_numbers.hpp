/*
2018 Maximilian Wittmer
wittmaxi@linux.pizza

https://github.com/Wittmaxi/ZENeural/blob/master/LICENSE

*/


#include <string>

TEST_CASE("Numbers")
{
    struct testFloatSerializerSerialize {
        testFloatSerializerSerialize() {
            CHECK (ZNN::Serializer<float>{}.serialize(3.1415).substr (0, 4) == "3.14");
            CHECK (ZNN::Serializer<float>{}.serialize(-3.1415).substr (0, 5) == "-3.14");
            CHECK (ZNN::Serializer<float>{}.serialize(3.14159261).substr (0, 6) == "3.1415");
        }
    };
    struct testFloatSerializerDeserialize {
        testFloatSerializerDeserialize() {
            CHECK (ZNN::Serializer<float>{}.deserialize("3.1415") == Approx (3.14).epsilon (0.3));
            CHECK (ZNN::Serializer<float>{}.deserialize("-3.1415") == Approx (-3.14).epsilon (0.3));
            CHECK (ZNN::Serializer<float>{}.deserialize("3.14159261") == Approx (3.1415).epsilon (0.3));
        }
    };
    struct testFloatSerializer {
        testFloatSerializer() {
            CHECK (ZNN::Serializer<float>{}.deserialize(ZNN::Serializer <float>{}.serialize(ZNN::Serializer<float>{}.deserialize("3.1415"))) == Approx (3.1415).epsilon (0.3));
            CHECK (ZNN::Serializer<float>{}.deserialize(ZNN::Serializer <float>{}.serialize(ZNN::Serializer<float>{}.deserialize("-3.1415"))) == Approx (-3.1415).epsilon (0.3));
            CHECK (ZNN::Serializer<float>{}.deserialize(ZNN::Serializer <float>{}.serialize(ZNN::Serializer<float>{}.deserialize("3.141592"))) == Approx (3.141592).epsilon (0.3));
        }
    };

    struct testDoubleSerializerSerialize {
        testDoubleSerializerSerialize() {
            CHECK (ZNN::Serializer<double>{}.serialize(3.1415).substr (0, 4) == "3.14");
            CHECK (ZNN::Serializer<double>{}.serialize(-3.1415).substr (0, 5) == "-3.14");
            CHECK (ZNN::Serializer<double>{}.serialize(3.14159261).substr (0, 6) == "3.1415");
        }
    };
    struct testDoubleSerializerDeserialize {
        testDoubleSerializerDeserialize() {
            CHECK (ZNN::Serializer<double>{}.deserialize("3.1415") == Approx (3.14).epsilon (0.3));
            CHECK (ZNN::Serializer<double>{}.deserialize("-3.1415") == Approx (-3.14).epsilon (0.3));
            CHECK (ZNN::Serializer<double>{}.deserialize("3.14159261") == Approx (3.1415).epsilon (0.3));
        }
    };
    struct testDoubleSerializer {
        testDoubleSerializer() {
            CHECK (ZNN::Serializer<double>{}.deserialize(ZNN::Serializer <double>{}.serialize(ZNN::Serializer<double>{}.deserialize("3.1415"))) == Approx (3.1415).epsilon (0.3));
            CHECK (ZNN::Serializer<double>{}.deserialize(ZNN::Serializer <double>{}.serialize(ZNN::Serializer<double>{}.deserialize("-3.1415"))) == Approx (-3.1415).epsilon (0.3));
            CHECK (ZNN::Serializer<double>{}.deserialize(ZNN::Serializer <double>{}.serialize(ZNN::Serializer<double>{}.deserialize("3.141592"))) == Approx (3.141592).epsilon (0.3));
        }
    };

    struct testLongDoubleSerializerSerialize {
        testLongDoubleSerializerSerialize() {
            CHECK (ZNN::Serializer<long double>{}.serialize(3.1415).substr (0, 4) == "3.14");
            CHECK (ZNN::Serializer<long double>{}.serialize(-3.1415).substr (0, 5) == "-3.14");
            CHECK (ZNN::Serializer<long double>{}.serialize(3.14159261).substr (0, 6) == "3.1415");
        }
    };
    struct testLongDoubleSerializerDeserialize {
        testLongDoubleSerializerDeserialize() {
            CHECK (ZNN::Serializer<long double>{}.deserialize("3.1415") == Approx (3.14).epsilon (0.3));
            CHECK (ZNN::Serializer<long double>{}.deserialize("-3.1415") == Approx (-3.14).epsilon (0.3));
            CHECK (ZNN::Serializer<long double>{}.deserialize("3.14159261") == Approx (3.1415).epsilon (0.3));
        }
    };
    struct testLongDoubleSerializer {
        testLongDoubleSerializer() {
            CHECK (ZNN::Serializer<long double>{}.deserialize(ZNN::Serializer <long double>{}.serialize(ZNN::Serializer<long double>{}.deserialize("3.1415"))) == Approx (3.1415).epsilon (0.3));
            CHECK (ZNN::Serializer<long double>{}.deserialize(ZNN::Serializer <long double>{}.serialize(ZNN::Serializer<long double>{}.deserialize("-3.1415"))) == Approx (-3.1415).epsilon (0.3));
            CHECK (ZNN::Serializer<long double>{}.deserialize(ZNN::Serializer <long double>{}.serialize(ZNN::Serializer<long double>{}.deserialize("3.141592"))) == Approx (3.141592).epsilon (0.3));
        }
    };

    testFloatSerializerDeserialize();
    testFloatSerializerDeserialize();
    testFloatSerializer();
    testDoubleSerializerDeserialize();
    testDoubleSerializerDeserialize();
    testDoubleSerializer();
    testLongDoubleSerializerDeserialize();
    testLongDoubleSerializerDeserialize();
    testLongDoubleSerializer();
}