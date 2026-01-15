#include "bitcoinkernel.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Notification Interface callbacks handler methods
void handle_block_tip(void* user_data, btck_SynchronizationState state, const btck_BlockTreeEntry* entry, double verification_progress)
{
    const char* state_str;
    switch (state)
    {
    case btck_SynchronizationState_INIT_REINDEX:
        state_str = "INIT_REINDEX";
        break;
    case btck_SynchronizationState_INIT_DOWNLOAD:
        state_str = "INIT_DOWNLOAD";
        break;
    case btck_SynchronizationState_POST_INIT:
        state_str = "POST_INIT";
        break;
    default:
        state_str = "UNKNOWN";
        break;
    }

    int32_t height = btck_block_tree_entry_get_height(entry);
    const btck_BlockHash* hash = btck_block_tree_entry_get_block_hash(entry);
    unsigned char hash_bytes[32];
    btck_block_hash_to_bytes(hash, hash_bytes);

    printf("[BLOCK_TIP] State: %s, Height: %d, Progress: %.2f%%\n", state_str, height, verification_progress * 100.0);
    printf("        Block Hash: ");
    for (int i = 0; i < 32; ++i) {
        printf("%02x", hash_bytes[i]);
    }
    printf("\n");
}

void handle_header_tip(void* user_data, btck_SynchronizationState state, int64_t height, int64_t timestamp, int presync)
{
    const char* state_str;
    switch (state)
    {
    case btck_SynchronizationState_INIT_REINDEX:
        state_str = "INIT_REINDEX";
        break;
    case btck_SynchronizationState_INIT_DOWNLOAD:
        state_str = "INIT_DOWNLOAD";
        break;
    case btck_SynchronizationState_POST_INIT:
        state_str = "POST_INIT";
        break;
    default:
        state_str = "UNKNOWN";
        break;
    }

    printf("[HEADER TIP] State: %s, Height: %ld, Timestamp: %ld, Presync: %s", 
            state_str, height, timestamp, presync ? "true" : "false");
}

void handle_progress(void* user_data, const char* title, size_t title_len, int progress_percent, int resume_possible)
{
    printf("[PROGRESS] %.*s: %d%% (Resume possible: %s)\n", (int)title_len, title, progress_percent, resume_possible ? "yes" : "no");
}

void handle_warning_set(void* user_data, btck_Warning warning, const char* message, size_t message_len)
{
    const char* warning_type;
    switch (warning) {
        case btck_Warning_UNKNOWN_NEW_RULES_ACTIVATED:
            warning_type = "UNKNOWN_NEW_RULES_ACTIVATED";
            break;
        case btck_Warning_LARGE_WORK_INVALID_CHAIN:
            warning_type = "LARGE_WORK_INVALID_CHAIN";
            break;
        default:
            warning_type = "UNKNOWN";
            break;
    }

    printf("[WARNING SET] Type: %s\n", warning_type);
    printf("        Message: %.*s\n", (int)message_len, message);
}

void handle_warning_unset(void* user_data, btck_Warning warning)
{
    const char* warning_type;
    switch (warning) {
        case btck_Warning_UNKNOWN_NEW_RULES_ACTIVATED:
            warning_type = "UNKNOWN_NEW_RULES_ACTIVATED";
            break;
        case btck_Warning_LARGE_WORK_INVALID_CHAIN:
            warning_type = "LARGE_WORK_INVALID_CHAIN";
            break;
        default:
            warning_type = "UNKNOWN";
            break;
    }

    printf("[WARNING UNSET] Type: %s", warning_type);
}

void handle_flush_error(void* user_data, const char* message, size_t message_len)
{
    printf("[FLUSH ERROR] %.*s\n", (int)message_len, message);
}

void handle_fatal_error(void* user_data, const char* message, size_t message_len)
{
    printf("[FATAL ERROR] %.*s\n", (int)message_len, message);
    exit(1);
}

// Validation Interface callback handler methods
void handle_block_checked(void* user_data, btck_Block* block, const btck_BlockValidationState* state)
{
    btck_ValidationMode mode = btck_block_validation_state_get_validation_mode(state);
    const char* mode_str;

    switch (mode) {
    case btck_ValidationMode_VALID:
        mode_str = "VALID";
        break;
    
    case btck_ValidationMode_INVALID:
        mode_str = "INVALID";
        break;
    
    case btck_ValidationMode_INTERNAL_ERROR:
        mode_str = "INTERNAL_ERROR";
        break;
    default:
        mode_str = "UNKNOWN";
        break;
    }

    btck_BlockHash* hash = btck_block_get_hash(block);
    unsigned char hash_bytes[32];
    btck_block_hash_to_bytes(hash, hash_bytes);

    printf("[BLOCK CHECKED] Validation: %s\n", mode_str);
    printf("        Block Hash: ");
    for (int i = 0; i < 32; ++i) {
        printf("%02x", hash_bytes[i]);
    }
    printf("\n");

    if (mode == btck_ValidationMode_INVALID) {
        btck_BlockValidationResult result = btck_block_validation_state_get_block_validation_result(state);
        const char* result_str;

        switch (result)
        {
        case btck_BlockValidationResult_UNSET:
            result_str = "UNSET";
            break;
        case btck_BlockValidationResult_CONSENSUS:
            result_str = "CONSENSUS";
            break;
        case btck_BlockValidationResult_CACHED_INVALID:
            result_str = "CACHED_INVALID";
            break;
        case btck_BlockValidationResult_HEADER_LOW_WORK:
            result_str = "HEADER_LOW_WORK";
            break;
        case btck_BlockValidationResult_INVALID_PREV:
            result_str = "INVALID_PREV";
            break;
        case btck_BlockValidationResult_MISSING_PREV:
            result_str = "MISSING_PREV";
            break;
        case btck_BlockValidationResult_TIME_FUTURE:
            result_str = "TIME_FUTURE";
            break;
        case btck_BlockValidationResult_MUTATED:
            result_str = "MUTATED";
            break;
        case btck_BlockValidationResult_INVALID_HEADER:
            result_str = "INVALID_HEADER";
            break;
        default:
            result_str = "UNKNOWN";
            break;
        }

        printf("            Validation Result: %s\n", result_str);
    }
    btck_block_hash_destroy(hash);
}

void handle_pow_valid_block(void* user_data, btck_Block* block, const btck_BlockTreeEntry* entry)
{
    int32_t height = btck_block_tree_entry_get_height(entry);
    btck_BlockHash* hash = btck_block_get_hash(block);
    unsigned char hash_bytes[32];
    btck_block_hash_to_bytes(hash, hash_bytes);

    printf("[POW_VALID_BLOCK] Height: %d\n", height);
    printf("                Block Hash: ");
    for (int i = 0; i < 32; ++i)
    {
        printf("%02x", hash_bytes[i]);
    }
    printf("\n");

    btck_block_hash_destroy(hash);
}

void handle_block_connected(void* user_data, btck_Block* block, const btck_BlockTreeEntry* entry)
{
    int32_t height = btck_block_tree_entry_get_height(entry);
    btck_BlockHash* hash = btck_block_get_hash(block);
    unsigned char hash_bytes[32];
    btck_block_hash_to_bytes(hash, hash_bytes);

    size_t tx_count = btck_block_count_transactions(block);

    printf("[BLOCK CONNECTED] Height: %d, Transactions: %zu\n", height, tx_count);
    printf("                  Block Hash: ");
        for (int i = 0; i < 32; i++) {
            printf("%02x", hash_bytes[i]);
        }
    printf("\n");
    
    btck_block_hash_destroy(hash);
}

  void handle_block_disconnected(void* user_data, btck_Block* block, const btck_BlockTreeEntry* entry)
{
    int32_t height = btck_block_tree_entry_get_height(entry);
    btck_BlockHash* hash = btck_block_get_hash(block);
    unsigned char hash_bytes[32];
    btck_block_hash_to_bytes(hash, hash_bytes);

    printf("[BLOCK_DISCONNECTED] Height: %d\n", height);
    printf("                     Block Hash: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", hash_bytes[i]);
    }
    printf("\n");

    btck_block_hash_destroy(hash);
}

void user_data_cleanup(void* user_data)
{
    if (user_data != NULL) {
        printf("[CLEANUP] Freeing user data at %p\n", user_data);
        free(user_data);
    }
}

int main()
{
    btck_ContextOptions* context_options = btck_context_options_create();
    btck_NotificationInterfaceCallbacks notifications_callbacks = {
        .user_data = NULL,
        .user_data_destroy = NULL,
        .block_tip = handle_block_tip,
        .header_tip = handle_header_tip,
        .progress = handle_progress,
        .warning_set = handle_warning_set,
        .warning_unset = handle_warning_unset,
        .flush_error = handle_flush_error,
        .fatal_error = handle_fatal_error,
    };

    btck_context_options_set_notifications(context_options, notifications_callbacks);
    btck_ValidationInterfaceCallbacks validation_interface_callbacks = {
        .user_data = NULL,
        .user_data_destroy = NULL,
        .block_checked = handle_block_checked,
        .pow_valid_block = handle_pow_valid_block,
        .block_connected = handle_block_connected,
        .block_disconnected = handle_block_disconnected
    };

    btck_context_options_set_validation_interface(context_options, validation_interface_callbacks);
    btck_ChainParameters* chain_params = btck_chain_parameters_create(btck_ChainType_REGTEST);
    btck_context_options_set_chainparams(context_options, chain_params);
    
    btck_Context* context = btck_context_create(context_options);
    btck_chain_parameters_destroy(chain_params);
    btck_context_options_destroy(context_options);
    if (context == NULL) {
        return 1;
    }

    const char data_dir[] = ".bitcoin";
    const char blocks_dir[] = ".bitcoin/blocks";

    btck_ChainstateManagerOptions* chainman_options = btck_chainstate_manager_options_create(context, data_dir, strlen(data_dir), blocks_dir, strlen(blocks_dir));
    const btck_ChainstateManagerOptions* chainman_options_ = chainman_options;
    if (chainman_options == NULL) {
        printf("Failed to create chainstate manager options");
        return 1;
    }

    btck_ChainstateManager* chainman = btck_chainstate_manager_create(chainman_options_);
    if (chainman == NULL) {
        printf("Failed to create Chainstate manager");    
        return 1;
    }

    btck_chainstate_manager_options_destroy(chainman_options);
    
    static const unsigned char block_data[] = {
        0x00, 0x00, 0x00, 0x20, 0x06, 0x22, 0x6e, 0x46, 0x11, 0x1a, 0x0b, 0x59, 0xca, 0xaf, 0x12, 0x60,
        0x43, 0xeb, 0x5b, 0xbf, 0x28, 0xc3, 0x4f, 0x3a, 0x5e, 0x33, 0x2a, 0x1f, 0xc7, 0xb2, 0xb7, 0x3c,
        0xf1, 0x88, 0x91, 0x0f, 0x29, 0x5b, 0xad, 0xc0, 0xbd, 0xd9, 0xa2, 0xbc, 0x09, 0x55, 0xd1, 0x2f,
        0x33, 0x74, 0x91, 0xea, 0xe4, 0xc8, 0x7b, 0xa4, 0x66, 0x00, 0x78, 0xc0, 0x15, 0x63, 0x10, 0x28,
        0x4d, 0x47, 0xc6, 0xff, 0x9a, 0x24, 0x2d, 0x66, 0xff, 0xff, 0x7f, 0x20, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x02, 0x51, 0x00, 0xff,
        0xff, 0xff, 0xff, 0x02, 0x00, 0xf2, 0x05, 0x2a, 0x01, 0x00, 0x00, 0x00, 0x16, 0x00, 0x14, 0x14,
        0x09, 0x74, 0x54, 0x05, 0xc4, 0xe8, 0x31, 0x0a, 0x87, 0x5b, 0xcd, 0x60, 0x2d, 0xb6, 0xb9, 0xb3,
        0xdc, 0x0c, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0x6a, 0x24, 0xaa, 0x21,
        0xa9, 0xed, 0xe2, 0xf6, 0x1c, 0x3f, 0x71, 0xd1, 0xde, 0xfd, 0x3f, 0xa9, 0x99, 0xdf, 0xa3, 0x69,
        0x53, 0x75, 0x5c, 0x69, 0x06, 0x89, 0x79, 0x99, 0x62, 0xb4, 0x8b, 0xeb, 0xd8, 0x36, 0x97, 0x4e,
        0x8c, 0xf9, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    btck_Block* block = btck_block_create(block_data, sizeof(block_data));
    if (block == NULL) {
        printf("Failed to create block");
        return 1;
    }

    int new_block = 1;
    int res = btck_chainstate_manager_process_block(chainman, block, &new_block);

    printf("\n[DEBUG] res=%d, new_block=%d\n", res, new_block);

    btck_block_destroy(block);
    btck_chainstate_manager_destroy(chainman);
    btck_context_destroy(context);

    printf("result %d\n", res);
    printf("new block %d\n", new_block);

    if (!res && new_block) {
        printf("Valid Block and Block Processed\n");
    } else if(!res && !new_block) {
        printf("Valid Duplicate Block\n");
    } else {
        printf("Invalid Block\n");
    }
}