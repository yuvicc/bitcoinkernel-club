# script_hex : 76a9144bfbaf6afb76cc5771bc6404810d1cc041a6933988ac
# amount : 0
# tx_hex : 02000000013f7cebd65c27431a90bba7f796914fe8cc2ddfc3f2cbd6f7e5f2fc854534da95000000006b483045022100de1ac3bcdfb0332207c4a91f3832bd2c2915840165f876ab47c5f8996b971c3602201c6c053d750fadde599e6f5c4e1963df0f01fc0d97815e8157e3d59fe09ca30d012103699b464d1d8bc9e47d4fb1cdaa89a1c5783d68363c4dbc4b524ed3d857148617feffffff02836d3c01000000001976a914fc25d6d5c94003bf5b0c7b640a248e2c637fcfb088ac7ada8202000000001976a914fbed3d9b11183209a57999d54d59f67c019e756c88ac6acb0700
# input idx : 0
# block header hex : 00c06a24d2ff376fa4cab6d28ac75ea4a38a675ac1cafa668cb601000000000000000000755926c6aa5c931b0b054c370746824f8935b35bd27172f1a36c07749b5cd60b9aa77869a1fc01171794522b

import pbk

def verify_script(script_pubkey_hex: str, amount: int, tx_to_hex: str, input_index: int) -> bool:
    script_pubkey = pbk.ScriptPubkey(bytes.fromhex(script_pubkey_hex))
    tx_to = pbk.Transaction(bytes.fromhex(tx_to_hex))
    return script_pubkey.verify(amount, tx_to, None ,input_index, pbk.ScriptVerificationFlags.ALL - pbk.ScriptVerificationFlags.TAPROOT)

# print(verify_script("76a9144bfbaf6afb76cc5771bc6404810d1cc041a6933988ac", 0, "02000000013f7cebd65c27431a90bba7f796914fe8cc2ddfc3f2cbd6f7e5f2fc854534da95000000006b483045022100de1ac3bcdfb0332207c4a91f3832bd2c2915840165f876ab47c5f8996b971c3602201c6c053d750fadde599e6f5c4e1963df0f01fc0d97815e8157e3d59fe09ca30d012103699b464d1d8bc9e47d4fb1cdaa89a1c5783d68363c4dbc4b524ed3d857148617feffffff02836d3c01000000001976a914fc25d6d5c94003bf5b0c7b640a248e2c637fcfb088ac7ada8202000000001976a914fbed3d9b11183209a57999d54d59f67c019e756c88ac6acb0700", 0))

# print(verify_script("76a9144bfbaf6afb76cc5771bc6404810d1cc041a6933988ac", 0, "02000000013f7cebd65c27431a90bba7f796914fe8cc2ddfc3f2cbd6f7e5f2fc854534da95000000006b483045022100de1ac3bcdfb0332207c4a91f3832bd2c2915840165f876ab47c5f8996b971c3602201c6c053d750fadde599e6f5c4e1963df0f01fc0d97815e8157e3d59fe09ca30d012103699b464d1d8bc9e47d4fb1cdaa89a1c5783d68363c4dbc4b524ed3d857148617feffffff02836d3c01000000001976a914fc25d6d5c94003bf5b0c7b640a248e2c637fcfb088ac7ada8202000000001976a914fbed3d9b11183209a57000d54d59f67c019e756c88ac6acb0700", 0))


def deserialize_block_header(block_header_hex: str):
    block_header = pbk.BlockHeader(bytes.fromhex(block_header_hex))
    print("nbits: ", block_header.bits)
    print("block hash: ", block_header.block_hash)
    print("nonce: ", block_header.nonce)
    print("prev hash: ", block_header.prev_hash)
    print("timestamp: ", block_header.timestamp)
    print("version: ", block_header.version)

# deserialize_block_header("0000003e1f17cb6d96514df941d952ccf6f1aed068d6da7eb46b0100000000000000000036718952ed9991b2f6b9c303d843c965c0b25f01ae6a5af5f90ecf748dbd5b2ae3d4056af01f0217047743c8")

def deserialize_block(raw_block_hex: str):
    block = pbk.Block(bytes.fromhex(raw_block_hex))
    consensus_params = pbk.ChainParameters(pbk.ChainType.REGTEST).consensus_params
    block_validation_state = block.check(consensus_params)
    print("Block Validation Result")
    print(block_validation_state.validation_mode == pbk.ValidationMode.VALID)
    print("Deserializing Block Data")
    print(block.block_hash)
    print(block.block_header.block_hash)
    print(block.block_header.nonce)
    print(block.transactions)


deserialize_block("0000002006226e46111a0b59caaf126043eb5bbf28c34f3a5e332a1fc7b2b73cf188910f295badc0bdd9a2bc0955d12f337491eae4c87ba4660078c0156310284d47c6ff9a242d66ffff7f200000000001020000000001010000000000000000000000000000000000000000000000000000000000000000ffffffff025100ffffffff0200f2052a010000001600141409745405c4e8310a875bcd602db6b9b3dc0cf90000000000000000266a24aa21a9ede2f61c3f71d1defd3fa999dfa36953755c690689799962b48bebd836974e8cf90120000000000000000000000000000000000000000000000000000000000000000000000000")

