from capgampy.instruments import CallPayOff, PutPayOff, OptionInfo
import pytest


@pytest.fixture
def setup():
    strike_price = 100
    yield strike_price


class TestInstruments:

    @pytest.mark.parametrize("spot_price,expected", [(125.0, 25.0), (75.0, 0.0)])
    def test_call_payoff(self, setup, spot_price, expected):
        strike_price = setup
        call_payoff = CallPayOff(strike_price)
        payoff_result = call_payoff.payoff(spot_price)
        assert payoff_result == expected

    @pytest.mark.parametrize("spot_price,expected", [(125.0, 0.0), (75.0, 25.0)])
    def test_put_payoff(self, setup, spot_price, expected):
        strike_price = setup
        put_payoff = PutPayOff(strike_price)
        payoff_result = put_payoff.payoff(spot_price)
        assert payoff_result == expected

    def test_opt_info_call_tte(self, setup):
        strike_price = setup
        opt_info = OptionInfo(CallPayOff(strike_price), 5)
        assert opt_info.get_time_to_exp() == 5

    def test_opt_info_put_tte(self, setup):
        strike_price = setup
        opt_info = OptionInfo(PutPayOff(strike_price), 5)
        assert opt_info.get_time_to_exp() == 5

    @pytest.mark.parametrize("spot_price,expected", [(125.0, 25.0), (75.0, 0.0)])
    def test_opt_info_call_payoff(self, setup, spot_price, expected):
        strike_price = setup
        opt_info = OptionInfo(CallPayOff(strike_price), 5)
        payoff_result = opt_info.payoff(spot_price)
        assert payoff_result == expected

    @pytest.mark.parametrize("spot_price,expected", [(125.0, 0.0), (75.0, 25.0)])
    def test_opt_info_put_payoff(self, setup, spot_price, expected):
        strike_price = setup
        opt_info = OptionInfo(PutPayOff(strike_price), 5)
        payoff_result = opt_info.payoff(spot_price)
        assert payoff_result == expected
