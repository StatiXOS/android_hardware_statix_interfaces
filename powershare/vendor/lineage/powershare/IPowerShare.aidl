package vendor.lineage.powershare;

@VintfStability
interface IPowerShare {
    int getMinBattery();

    boolean isEnabled();

    boolean setEnabled(in boolean enable);

    int setMinBattery(in int minBattery);
}
