import capgampy
import pytest


@pytest.fixture
def setup():
    strike_price = 100
    yield strike_price


class TestCallOptionPayoff:

    @pytest.mark.parametrize("spot_price,expected", [(125.0, 25.0), (75.0, 0.0)])
    def test_call_payoff(self, setup, spot_price, expected):
        strike_price = setup
        call_payoff = capgampy.CallPayOff(strike_price)
        payoff_result = call_payoff.payoff(spot_price)
        assert payoff_result == expected

    @pytest.mark.parametrize("spot_price,expected", [(125.0, 0.0), (75.0, 25.0)])
    def test_put_payoff(self, setup, spot_price, expected):
        strike_price = setup
        put_payoff = capgampy.PutPayOff(strike_price)
        payoff_result = put_payoff.payoff(spot_price)
        assert payoff_result == expected
