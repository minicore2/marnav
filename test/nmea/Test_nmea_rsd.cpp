#include <gtest/gtest.h>
#include <marnav/nmea/rsd.hpp>
#include <marnav/nmea/nmea.hpp>
#include "type_traits_helper.hpp"

namespace
{

using namespace marnav;

class Test_nmea_rsd : public ::testing::Test
{
};

TEST_F(Test_nmea_rsd, contruction)
{
	EXPECT_NO_THROW(nmea::rsd rsd);
}

TEST_F(Test_nmea_rsd, properties)
{
	nmea_sentence_traits<nmea::rsd>();
}

TEST_F(Test_nmea_rsd, parse)
{
	auto s = nmea::make_sentence("$IIRSD,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,A,A*47");
	ASSERT_NE(nullptr, s);

	auto rsd = nmea::sentence_cast<nmea::rsd>(s);
	ASSERT_NE(nullptr, rsd);
}

TEST_F(Test_nmea_rsd, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rsd>(nmea::talker::none, {12, "@"}));
	EXPECT_ANY_THROW(
		nmea::detail::factory::sentence_parse<nmea::rsd>(nmea::talker::none, {14, "@"}));
}

TEST_F(Test_nmea_rsd, empty_to_string)
{
	nmea::rsd rsd;

	EXPECT_STREQ("$IIRSD,0,0,0,0,0,0,0,0,0,0,0,V,C*4C", nmea::to_string(rsd).c_str());
}
}
