package com.cpad_lab2;

import java.util.Date;

public class CisMember  extends Country  {
    private final int cisId;
    private final Date entryDate;

    CisMember(final String countryName, final String countryCode, final int cisId, final Date entryDate) {
        super(countryName, countryCode);

        this.cisId = cisId;
        this.entryDate = entryDate;
    }

    CisMember(final Country country, final int cisId, final Date entryDate) {
        super(country.getName(), country.getCountryCode());

        this.cisId = cisId;
        this.entryDate = entryDate;
    }

    public int getCisId() {
        return cisId;
    }

    public Date getEntryDate() {
        return entryDate;
    }
}
