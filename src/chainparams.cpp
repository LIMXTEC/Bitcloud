// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2015-2017 The BTDX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x000002d56463941c20eae5cb474cc805b646515d18bc7dc222a0885b206eadb0"))
    (300, uint256("0x00000b5361a581aa6bae68175c4c4599e844ef935e95d37af55542e0f635f28c")) // last PoW Block
    (1000, uint256("0x2a0dd7730224a2c3b3a25d1772c23aa4cb42dc2dffa395d143e55e9a9a2afc06"))
    (5000, uint256("0x3fbcc4902368fb0628268b1198f5b9d0246fa907384d4f897d06b11150dd4313"))
    (10000, uint256("0xfd54eb8669e674842c5298fe0e54312034d7ba7235c48afe37150058e8fc40c2"))
    (25000, uint256("0xccd1dce5db2954dfb2b35f4569038e4a1dcf1af3df3e5997bb451e6718ba8354"))
    (50000, uint256("0x3b790274950f1d34b34fe7afb404ed57bfe01048ae7ffb4955803d3711110999"))
    (75000, uint256("0xeccff76714cb4c8fb711b80abceb4d2dae67d14afb256ba7eeb1e6b719f459d9"))
    (82499, uint256("0x812232aa0007f1e2a5f03aa4738ecc7cb6e0a60a8bf83e9a3a7c8ac78ede46d2"))
    (82500, uint256("0x855b1b87bfc850560126dbc3a4e10bc3e6b38b2a99e49cdc95a86fa570871256"))
    (100000, uint256("0x4789e3f2559025345c2d5e819b97b236605fb2da2ecd917a00cb79d71ee075b2"))
    (108000, uint256("0x4d5d78d85b007599426fca0522279c31770fe7178e8b453526425b97c4878e43"))
	(144560, uint256("0x3cfbbaa9a2a4e37f901bb6d4dc87cb48b11baf035a8022faf1e9672021764ace"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1547062532, // * UNIX timestamp of last checkpoint block
    291584,     // * total number of transactions between genesis and last checkpoint
                //  (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1454124731,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xe4;
        pchMessageStart[1] = 0xe8;
        pchMessageStart[2] = 0xbd;
        pchMessageStart[3] = 0xfd;
        vAlertPubKey = ParseHex("0000098d3ba6ba6e7423fa5cbd6a89e0a9a5348f88d332b44a5cb1a8b7ed2c1eaa335fc8dc4f012cb8241cc0bdafd6ca70c5f5448916e4e6f511bcd746ed57dc50");
        nDefaultPort = 8329;  //8329
        bnProofOfWorkLimit = ~uint256(0) >> 20; // BTDX starting difficulty is 1 / 2^12  //20
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 300; // BTDX: 3 hours // 1 day
        nTargetSpacing = 1 * 300;  // BTDX: 135 sec
        nLastPOWBlock = 300;
        nMaturity = 144;
        nMasternodeCountDrift = 20;
		nMasternodeColleteralLimxDev = 10000; //Params().MasternodeColleteralLimxDev()
        nModifierUpdateBlock = 1; // we use the version 2 for dmd
        nMaxMoneyOut = 21000000 * COIN;
/*
		printf("Searching for genesis block...\n");
        assert(hashGenesisBlock == uint256("0x00008412c3a4bbf7133c9cfbb8f9041fdd39bc98d1e1527612d10d95ed9b06d1"));
uint256 hashTarget = uint256().SetCompact(genesis.nBits);
        assert(genesis.hashMerkleRoot == uint256("0xb4bf3c8018489a8af30346984ead81659b1b91f5e7bc856eb7e2c4e3db122f36"));
uint256 thash;

while (true)
{
    thash = genesis.GetHash();
    if (thash <= hashTarget)
        break;
    if ((genesis.nNonce & 0xFFF) == 0)
    {
        printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
    }
    ++genesis.nNonce;
    if (genesis.nNonce == 0)
    {
        printf("NONCE WRAPPED, incrementing time\n");
        ++genesis.nTime;
    }
}
printf("genesis.nTime = %u \n", genesis.nTime);
printf("genesis.nNonce = %u \n", genesis.nNonce);
printf("genesis.nVersion = %u \n", genesis.nVersion);
printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str());
*/

        /*
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         //Testblock
         python genesis.py -a quark -z "The times 31.08.2016 Bitcloud was founded - Designed Team Bitsend" -t 1502817296 -v 0
         Z:\VMS\Gen\genquark>python genesis.py -a quark -z "The times 31.08.2016 Bitcloud was founded - Designed Team Bitsend" -t 1502817296 -v 0
04ffff001d0104415468652074696d65732033312e30382e3230313620426974636c6f75642077617320666f756e646564202d2044657369676e6564205465616d2042697473656e64
algorithm: quark
merkle hash: 68f38e0fb1ea4346fa70aee7799c5f952293644e9ffdeccac41173e1e10e07cb
pszTimestamp: The times 31.08.2016 Bitcloud was founded - Designed Team Bitsend
pubkey: 04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f
time: 1502817296
bits: 0x1e0ffff0
Searching for genesis hash..
genesis hash found!
nonce: 934213
genesis hash: 000002d56463941c20eae5cb474cc805b646515d18bc7dc222a0885b206eadb0
         */
        const char* pszTimestamp = "The times 31.08.2016 Bitcloud was founded - Designed Team Bitsend";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1502817296;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 934213;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000002d56463941c20eae5cb474cc805b646515d18bc7dc222a0885b206eadb0"));
        assert(genesis.hashMerkleRoot == uint256("0x68f38e0fb1ea4346fa70aee7799c5f952293644e9ffdeccac41173e1e10e07cb"));

        vSeeds.push_back(CDNSSeedData("seed.bitcloud.network", "seed.bitcloud.network"));
        vSeeds.push_back(CDNSSeedData("188.68.52.172", "188.68.52.172"));
        vSeeds.push_back(CDNSSeedData("37.120.186.85", "37.120.186.85"));
        vSeeds.push_back(CDNSSeedData("37.120.190.76", "37.120.190.76"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 5);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md 109 	0x8000006d
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x6d).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true; //true
        fAllowMinDifficultyBlocks = false; //true
        fDefaultConsistencyChecks = false;
        fRequireStandard = true; // true
        fMineBlocksOnDemand = false; //false
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        /*
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        */

        nPoolMaxTransactions = 3;
        strSporkKey = "04DA111581AB2E25EB1F0AD98E0CC168EDE663C6282B0FF7C20B33D205E9F0F8A1B4905CC81B2003D2AFA360BE9A317CD130B4530EABDB182FDC50202E28F28659";
        strDarksendPoolDummyAddress = "BHC9RXJiBkfsmC6edT61hRNq2NZMPe3unJ";
        nStartMasternodePayments = 1514332800; //12/27/2017 @ 12:00am (UTC)
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/*
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        vAlertPubKey = ParseHex("000010e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9");
        nDefaultPort = 51474;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 135; // BTDX: 1 day
        nTargetSpacing = 1 * 135;  // BTDX: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;


        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1502817296;
        genesis.nNonce = 934213;


        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000002d56463941c20eae5cb474cc805b646515d18bc7dc222a0885b206eadb0"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("188.68.52.172", "188.68.52.172"));
        vSeeds.push_back(CDNSSeedData("37.120.186.85", "37.120.186.85"));
        vSeeds.push_back(CDNSSeedData("37.120.190.76", "37.120.190.76"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet bitcloud addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet bitcloud script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet bitcloud BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet bitcloud BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet bitcloud BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));


        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;



        nPoolMaxTransactions = 2;
        strSporkKey = "04982ABC443EB2F4A9EB73B9ED73456CAAB10071A2DED9761BCFDE1997B55BA810C3A95415D203296ADAE60F8DF348941C0DA1FCD70137C0069207CEE213C33E23";
        strDarksendPoolDummyAddress = "y9GT3SSVAditTmC2ZkykzeDpg9zmCYMwEw";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Bitcloud: 1 day
        nTargetSpacing = 1 * 60;        // Bitcloud: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1502817296;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 934213;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;
        assert(hashGenesisBlock == uint256("0x000002d56463941c20eae5cb474cc805b646515d18bc7dc222a0885b206eadb0"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
