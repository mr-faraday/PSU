package com.cpad_lab2;

import java.util.Date;

public class NatoMember extends Country {
    private final Date entryDate;
    private final String role;

    NatoMember(final String countryName, final String countryCode, final Date entryDate, final String role) {
        super(countryName, countryCode);

        this.entryDate = entryDate;
        this.role = role;
    }

    NatoMember(final Country country, final Date entryDate, final String role) {
        super(country.getName(), country.getCountryCode());

        this.entryDate = entryDate;
        this.role = role;
    }

    public Date getEntryDate() {
        return entryDate;
    }

    public String getRole() {
        return role;
    }
}
