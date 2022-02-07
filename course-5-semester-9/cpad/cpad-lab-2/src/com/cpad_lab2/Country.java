package com.cpad_lab2;

public class Country {
    private String name;
    private String countryCode;

    Country(final String name, final String countyCode) {
        this.name = name;
        this.countryCode = countyCode;
    }

    public String getName() {
        return name;
    }
    public Country setName(final String name) {
        this.name = name;
        return this;
    }

    public String getCountryCode() {
        return countryCode;
    }
    public Country setCountryCode (final String code) {
        this.countryCode = code;
        return this;
    }
}
